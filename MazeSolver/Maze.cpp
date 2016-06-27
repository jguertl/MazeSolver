//------------------------------------------------------------------------------
// Maze.cpp
//
// Group: Group 10, study assistant: Daniel Ellmeier
//
// Authors: Peter Buerscher (1530750)
// Jakob Guertl (1530763)
//------------------------------------------------------------------------------
//

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <algorithm>
#include "Game.h"
#include "Maze.h"
#include "Tile.h"
#include "Wall.h"
#include "Path.h"
#include "Ice.h"
#include "Start.h"
#include "Finish.h"
#include "Bonus.h"
#include "Quicksand.h"
#include "Teleport.h"
#include "OneWay.h"
#include "Hole.h"
#include "Counter.h"
#include "FileOpenException.h"
#include "FileAccessException.h"
#include "InvalidFileException.h"
#include "InvalidPathException.h"
#include "NoMoreStepsException.h"
#include "InvalidMoveException.h"
#include "NoPathFoundException.h"
#include "AlreadySolvedException.h"

using std::ofstream;
using std::ifstream;
using std::string;
using std::cout;
using std::endl;
using std::sort;
using std::move;

const string Maze::OUTPUT_REMAINING_STEPS = "Remaining Steps: ";
const string Maze::OUTPUT_MOVED_STEPS = "Moved Steps: ";
const string Maze::SAVE_FILE_NAME = "save_file.txt";
const string Maze::NUMBERS = "0123456789";
const string Maze::SOLVED_APPEND = "Solved";
const char Maze::FAST_MOVE_FLAG = 'f';
const char Maze::ICE_MOVE_FLAG = 'i';
const char Maze::FIELD_TYPE_PLAYER = '*';
const char Maze::FIELD_TYPE_WALL = '#';
const char Maze::FIELD_TYPE_ICE = '+';
const char Maze::FIELD_TYPE_PATH = ' ';
const char Maze::FIELD_TYPE_START = 'o';
const char Maze::FIELD_TYPE_FINISH = 'x';
const char Maze::FIELD_TYPE_TELEPORT_MIN = 'A';
const char Maze::FIELD_TYPE_TELEPORT_MAX = 'Z';
const char Maze::FIELD_TYPE_BONUS_MIN = 'a';
const char Maze::FIELD_TYPE_BONUS_MAX = 'e';
const char Maze::FIELD_TYPE_QUICKSAND_MIN = 'f';
const char Maze::FIELD_TYPE_QUICKSAND_MAX = 'j';
const char Maze::FIELD_TYPE_ONEWAY_UP = '^';
const char Maze::FIELD_TYPE_ONEWAY_DOWN = 'v';
const char Maze::FIELD_TYPE_ONEWAY_LEFT = '<';
const char Maze::FIELD_TYPE_ONEWAY_RIGHT = '>';
const char Maze::FIELD_TYPE_HOLE = 's';
const char Maze::FIELD_TYPE_COUNTER_MIN = '1';
const char Maze::FIELD_TYPE_COUNTER_MAX = '9';
const char Maze::COUNTER_ZERO_CHAR = '0';
const char Maze::FILENAME_DEFINITION_LOWERCASE_MIN = 'a';
const char Maze::FILENAME_DEFINITION_LOWERCASE_MAX = 'z';
const char Maze::FILENAME_DEFINITION_UPPERCASE_MIN = 'A';
const char Maze::FILENAME_DEFINITION_UPPERCASE_MAX = 'Z';
const char Maze::FILENAME_DEFINITION_NUMBER_MIN = '0';
const char Maze::FILENAME_DEFINITION_NUMBER_MAX = '9';
const char Maze::FILENAME_DEFINITION_DOT = '.';
const char Maze::FILENAME_DEFINITION_SLASH = '/';
const int Maze::FILENAME_MAX_SIZE = 255;
const char Maze::NEW_LINE = '\n';
const int Maze::SOLVE_BONUS_CORRECTION = 5;
const int Maze::COUNTER_MIN_VALUE = 1;
const int Maze::BONUS_OFFSET = 1;
const int Maze::QUICKSAND_OFFSET = 1;
const int Maze::GAME_WON = 1;
const int Maze::SUCCESS = 0;
const int Maze::EQUAL = 0;
const int Maze::ERROR = -1;
const int Maze::OUT_OF_STEPS = -2;
const int Maze::INVALID_MOVE = -3;
const int Maze::INVALID_PATH = -4;
const int Maze::INITIALIZE_ZERO = 0;
const int Maze::INITIALIZE_NEGATIVE = -1;


// from: http://rosettacode.org/wiki/Dijkstra%27s_algorithm#C.2B.2B
// begin

void dijkstraComputePaths(vertex_t source,
                          const adjacency_list_t &adjacency_list,
                          std::vector<weight_t> &min_distance,
                          std::vector<vertex_t> &previous)
{
    int n = adjacency_list.size();
    min_distance.clear();
    min_distance.resize(n, max_weight_);
    min_distance[source] = 0;
    previous.clear();
    previous.resize(n, -1);
    std::set<std::pair<weight_t, vertex_t> > vertex_queue;
    vertex_queue.insert(std::make_pair(min_distance[source], source));

    while (!vertex_queue.empty())
    {
        weight_t dist = vertex_queue.begin()->first;
        vertex_t u = vertex_queue.begin()->second;
        vertex_queue.erase(vertex_queue.begin());

        // Visit each edge exiting u
	const std::vector<neighbor> &neighbors = adjacency_list[u];
        for (std::vector<neighbor>::const_iterator neighbor_iter = neighbors.begin();
             neighbor_iter != neighbors.end();
             neighbor_iter++)
        {
            vertex_t v = neighbor_iter->target;
            weight_t weight = neighbor_iter->weight;
            weight_t distance_through_u = dist + weight;
	    if (distance_through_u < min_distance[v]) {
	        vertex_queue.erase(std::make_pair(min_distance[v], v));

	        min_distance[v] = distance_through_u;
	        previous[v] = u;
	        vertex_queue.insert(std::make_pair(min_distance[v], v));

	    }

        }
    }
}

std::list<vertex_t> dijkstraGetShortestPathTo(
    vertex_t vertex, const std::vector<vertex_t> &previous)
{
    std::list<vertex_t> path;
    for ( ; vertex != -1; vertex = previous[vertex])
        path.push_front(vertex);
    return path;
}
// end

//------------------------------------------------------------------------------
Maze::Maze() : steps_(0), solved_steps_(0)
{
}

//------------------------------------------------------------------------------
Maze::~Maze()
{
}

//------------------------------------------------------------------------------
int Maze::load(const string& path)
{
  filename_ = path;
  ifstream file (path);
  string line;
  string moves_save = moves_;
  char buffer = INITIALIZE_ZERO;
  char buffer_check = INITIALIZE_ZERO;
  char teleport_duplicate_check = INITIALIZE_ZERO;
  int start_check = INITIALIZE_ZERO;
  int finish_check = INITIALIZE_ZERO;
  unique_ptr<Tile> unique_buffer;
  vector < unique_ptr<Tile> > unique_vector_buffer;
  vector<char> teleport_symbols;
  std::stringstream sstream (std::stringstream::in | std::stringstream::out);
  bool maze_loaded = false;
  int size_check = INITIALIZE_NEGATIVE;
  int counter_x = INITIALIZE_ZERO;
  int counter_y = INITIALIZE_ZERO;
  int counter_id = INITIALIZE_NEGATIVE;

  if(tiles_.size())
  {
    maze_loaded = true;
    save(SAVE_FILE_NAME);
    deleteMaze();
  }

  if (file.is_open())
  {
    std::getline(file, moves_);
    // Check if file is not empty
    if(file.eof())
    {
      file.close();
      if(maze_loaded)
      {
        deleteMaze();
        load(SAVE_FILE_NAME);
        fastMovePlayer(moves_save);
      }
      throw InvalidFileException();
    }

    std::getline(file, line);
    // Check if file and line are not empty
    if(file.eof() || line.empty())
    {
      file.close();
      if(maze_loaded)
      {
        deleteMaze();
        load(SAVE_FILE_NAME);
        fastMovePlayer(moves_save);
      }
      throw InvalidFileException();
    }

    // Check if line only contains a number
    if(line.find_first_not_of(NUMBERS) != string::npos)
    {
      file.close();
      if(maze_loaded)
      {
        deleteMaze();
        load(SAVE_FILE_NAME);
        fastMovePlayer(moves_save);
      }
      throw InvalidFileException();
    }

    sstream << line;
    sstream >> original_steps_;
    steps_ = original_steps_;
    sstream.str("");
    sstream.clear();

    counter_x = INITIALIZE_ZERO;
    counter_y = INITIALIZE_ZERO;
    // Check if moves are valid
    while(counter_x < (static_cast<int>(moves_.size())))
    {
      if((moves_.at(counter_x) != Game::DIRECTION_FAST_MOVE_UP) &&
        (moves_.at(counter_x) != Game::DIRECTION_FAST_MOVE_DOWN) &&
        (moves_.at(counter_x) != Game::DIRECTION_FAST_MOVE_LEFT) &&
        (moves_.at(counter_x) != Game::DIRECTION_FAST_MOVE_RIGHT))
      {
        file.close();
        if(maze_loaded)
        {
          deleteMaze();
          load(SAVE_FILE_NAME);
          fastMovePlayer(moves_save);
        }
        throw InvalidFileException();
      }
      counter_x++;
    }

    // Check if steps are valid
    if(static_cast<int>(moves_.size()) > steps_)
    {
      file.close();
      if(maze_loaded)
      {
        deleteMaze();
        load(SAVE_FILE_NAME);
        fastMovePlayer(moves_save);
      }
      throw InvalidPathException();
    }

    counter_x = INITIALIZE_ZERO;
    while(file.get(buffer))
    {
      // Store the buffer to check if the last char is a linebreak
      buffer_check = buffer;

      if(buffer == FIELD_TYPE_WALL)
      {
        // Wall
        unique_buffer = unique_ptr<Tile>(new Wall(buffer, INITIALIZE_NEGATIVE,
          INITIALIZE_ZERO));
        unique_vector_buffer.push_back(move(unique_buffer));
      }
      else if(buffer == FIELD_TYPE_PATH)
      {
        // Path
        counter_id++;
        unique_buffer = unique_ptr<Tile>(new Path(buffer, counter_id,
          INITIALIZE_ZERO));
        unique_vector_buffer.push_back(move(unique_buffer));
      }
      else if(buffer == FIELD_TYPE_ICE)
      {
        // Ice
        counter_id++;
        unique_buffer = unique_ptr<Tile>(new Ice(buffer, counter_id,
          INITIALIZE_ZERO));
        unique_vector_buffer.push_back(move(unique_buffer));
      }
      else if(buffer == FIELD_TYPE_START)
      {
        // Start
        counter_id++;
        unique_buffer = unique_ptr<Tile>(new Start(buffer, counter_id,
          INITIALIZE_ZERO));
        unique_vector_buffer.push_back(move(unique_buffer));
        player_.setX(counter_x);
        player_.setY(counter_y);
        start_id_ = counter_id;
        start_check++;
      }
      else if(buffer == FIELD_TYPE_FINISH)
      {
        // Finish
        counter_id++;
        unique_buffer = unique_ptr<Tile>(new Finish(buffer, counter_id,
          INITIALIZE_ZERO));
        unique_vector_buffer.push_back(move(unique_buffer));
        finish_id_ = counter_id;
        finish_check++;
      }
      else if((buffer >= FIELD_TYPE_BONUS_MIN) &&
        (buffer <= FIELD_TYPE_BONUS_MAX))
      {
        // Bonus
        counter_id++;
        unique_buffer = unique_ptr<Tile>(new Bonus(buffer, counter_id,
          (buffer - FIELD_TYPE_BONUS_MIN + BONUS_OFFSET)));
        unique_vector_buffer.push_back(move(unique_buffer));
        bonus_id_list.push_back(counter_id);
      }
      else if((buffer >= FIELD_TYPE_QUICKSAND_MIN) &&
        (buffer <= FIELD_TYPE_QUICKSAND_MAX))
      {
        // Quicksand
        counter_id++;
        unique_buffer = unique_ptr<Tile>(new Quicksand(buffer, counter_id,
          ((buffer - FIELD_TYPE_QUICKSAND_MIN) + QUICKSAND_OFFSET)));
        unique_vector_buffer.push_back(move(unique_buffer));
      }
      else if((buffer >= FIELD_TYPE_TELEPORT_MIN) &&
        (buffer <= FIELD_TYPE_TELEPORT_MAX))
      {
        // Teleport
        counter_id++;
        unique_buffer = unique_ptr<Tile>(new Teleport(buffer, counter_id,
          INITIALIZE_ZERO));
        unique_vector_buffer.push_back(move(unique_buffer));

        teleport_symbols.push_back(buffer);
      }
      else if(buffer == FIELD_TYPE_HOLE)
      {
        // Hole
        counter_id++;
        unique_buffer = unique_ptr<Tile>(new Hole(buffer, counter_id,
          INITIALIZE_ZERO));
        unique_vector_buffer.push_back(move(unique_buffer));
      }
      else if((buffer >= FIELD_TYPE_COUNTER_MIN) &&
              (buffer <= FIELD_TYPE_COUNTER_MAX))
      {
        // Counter
        counter_id++;
        unique_buffer = unique_ptr<Tile>(new Counter(buffer, counter_id,
          buffer - COUNTER_ZERO_CHAR));
        unique_vector_buffer.push_back(move(unique_buffer));
      }
      else if((buffer == FIELD_TYPE_ONEWAY_LEFT) ||
        (buffer == FIELD_TYPE_ONEWAY_RIGHT) ||
        (buffer == FIELD_TYPE_ONEWAY_UP) ||
        (buffer == FIELD_TYPE_ONEWAY_DOWN))
      {
        // OneWay
        counter_id++;
        unique_buffer = unique_ptr<Tile>(new OneWay(buffer, counter_id,
          INITIALIZE_ZERO));
        unique_vector_buffer.push_back(move(unique_buffer));
      }
      else if(buffer != NEW_LINE)
      {
        file.close();
        if(maze_loaded)
        {
          deleteMaze();
          load(SAVE_FILE_NAME);
          fastMovePlayer(moves_save);
        }
        throw InvalidFileException();
      }

      counter_x++;
      if(buffer == NEW_LINE)
      {
        // Check if width is greater than zero
        if(static_cast<int>(unique_vector_buffer.size()) == EQUAL)
        {
          file.close();
          if(maze_loaded)
          {
            deleteMaze();
            load(SAVE_FILE_NAME);
            fastMovePlayer(moves_save);
          }
          throw InvalidFileException();
        }

        // Check Maze
        if((size_check >= EQUAL) && (size_check !=
          static_cast<int>(unique_vector_buffer.size())))
        {
          file.close();
          if(maze_loaded)
          {
            deleteMaze();
            load(SAVE_FILE_NAME);
            fastMovePlayer(moves_save);
          }
          throw InvalidFileException();
        }

        // Check if leading and trailing # are valid
        if((unique_vector_buffer.front()->getSymbol() != FIELD_TYPE_WALL) &&
           (unique_vector_buffer.back()->getSymbol() != FIELD_TYPE_WALL))
        {
          file.close();
          if(maze_loaded)
          {
            deleteMaze();
            load(SAVE_FILE_NAME);
            fastMovePlayer(moves_save);
          }
          throw InvalidFileException();
        }

        size_check = static_cast<int>(unique_vector_buffer.size());
        tiles_.push_back(move(unique_vector_buffer));
        unique_vector_buffer.clear();
        counter_y++;
        counter_x = INITIALIZE_ZERO;
      }
    }

    // Check if maze is not empty and if last character is a linebreak
    if( !(tiles_.size()) ||
       (buffer_check != NEW_LINE))
    {
      file.close();
      deleteMaze();
      if(maze_loaded)
      {
        load(SAVE_FILE_NAME);
        fastMovePlayer(moves_save);
      }
      throw InvalidFileException();
    }

    // Check if first line only contains Walls
    for(counter_x = 0; counter_x < static_cast<int>(tiles_.front().size());
      counter_x++)
    {
      if((tiles_.front().at(counter_x)->getSymbol()) != FIELD_TYPE_WALL)
      {
        file.close();
        deleteMaze();
        if(maze_loaded)
        {
          load(SAVE_FILE_NAME);
          fastMovePlayer(moves_save);
        }
        throw InvalidFileException();
      }
    }

    // Check if last line only contains Walls
    counter_x = INITIALIZE_ZERO;
    for(counter_x = 0; counter_x < static_cast<int>(tiles_.back().size());
      counter_x++)
    {

      if((tiles_.back().at(counter_x)->getSymbol()) != FIELD_TYPE_WALL)
      {
        file.close();
        deleteMaze();
        if(maze_loaded)
        {
          load(SAVE_FILE_NAME);
          fastMovePlayer(moves_save);
        }
        throw InvalidFileException();
      }
    }

    // Check if one start and one finish are in the Maze
    if((start_check != 1) || (finish_check != 1))
    {
      file.close();
      deleteMaze();
      if(maze_loaded)
      {
        load(SAVE_FILE_NAME);
        fastMovePlayer(moves_save);
      }
      throw InvalidFileException();
    }

    // Check all Teleports
    teleport_duplicate_check = INITIALIZE_ZERO;
    sort(teleport_symbols.begin(), teleport_symbols.end());
    while(teleport_symbols.size() > 1)
    {
      buffer = teleport_symbols.back();
      if(buffer == teleport_duplicate_check)
      {
        file.close();
        deleteMaze();
        if(maze_loaded)
        {
          load(SAVE_FILE_NAME);
          fastMovePlayer(moves_save);
        }
        throw InvalidFileException();
      }
      teleport_duplicate_check = buffer;
      teleport_symbols.pop_back();
      if(buffer != teleport_symbols.back())
      {
        file.close();
        deleteMaze();
        if(maze_loaded)
        {
          load(SAVE_FILE_NAME);
          fastMovePlayer(moves_save);
        }
        throw InvalidFileException();
      }
      teleport_symbols.pop_back();
    }
    if(teleport_symbols.size())
    {
      file.close();
      deleteMaze();
      if(maze_loaded)
      {
        load(SAVE_FILE_NAME);
        fastMovePlayer(moves_save);
      }
      throw InvalidFileException();
    }

    player_.setTile(tiles_.at(player_.getY()).at(player_.getX())->getSymbol());
    file.close();
    save(SAVE_FILE_NAME);

    moves_save = moves_;
    if(fastMovePlayerLoad(moves_) == GAME_WON)
    {
      moves_ = moves_save;
      return GAME_WON;
    }

    moves_ = moves_save;
  }
  else
  {
    deleteMaze();
    if(maze_loaded)
    {
      load(SAVE_FILE_NAME);
      fastMovePlayer(moves_save);
    }
    throw FileOpenException();
  }
  counter_id++;
  resetAdjacencyList();
  adjacency_list_.resize(counter_id);
  is_adjacency_generated_ = false;
  return SUCCESS;
}

//------------------------------------------------------------------------------
int Maze::reset()
{
  return(load(SAVE_FILE_NAME));
}

//------------------------------------------------------------------------------
int Maze::save(const string& path)
{
  int counter_x = INITIALIZE_ZERO;
  int counter_y = INITIALIZE_ZERO;
  ofstream outputfile;
  outputfile.open(path.c_str());
  string moves_save;

  if(outputfile.fail())
  {
    throw FileAccessException();
  }

  if(path == SAVE_FILE_NAME)
  {
    outputfile << endl;
  }
  else
  {
    outputfile << moves_ << endl;
    moves_save = moves_;
  }

  outputfile << original_steps_ << endl;

  for (counter_y = 0; counter_y < static_cast<int>(tiles_.size());
    counter_y++)
  {
    for (counter_x = 0;
      counter_x < static_cast<int>(tiles_.at(counter_y).size());
      counter_x++)
    {
      if(((tiles_.at(counter_y).at(counter_x)->getSymbol() >= FIELD_TYPE_COUNTER_MIN) &&
        (tiles_.at(counter_y).at(counter_x)->getSymbol() <= FIELD_TYPE_COUNTER_MAX)) ||
        ((tiles_.at(counter_y).at(counter_x)->getSymbol() == FIELD_TYPE_WALL) &&
        (tiles_.at(counter_y).at(counter_x)->getValue() != INITIALIZE_ZERO)))
      {
        outputfile << tiles_.at(counter_y).at(counter_x)->getValue();
      }
      else
      {
        outputfile << tiles_.at(counter_y).at(counter_x)->getSymbol();
      }
    }
    outputfile << endl;
  }
  outputfile.close();
  return SUCCESS;
}

//------------------------------------------------------------------------------
int Maze::show()
{
  int counter_x = INITIALIZE_ZERO;
  int counter_y = INITIALIZE_ZERO;
  for (counter_y = 0; counter_y < static_cast<int>(tiles_.size());
    counter_y++)
  {
    for (counter_x = 0; counter_x <
      static_cast<int>(tiles_.at(counter_y).size());
      counter_x++)
    {
      if((counter_y == player_.getY()) && (counter_x == player_.getX()))
      {
        cout << FIELD_TYPE_PLAYER;
      }
      else
      {
        if((tiles_.at(counter_y).at(counter_x)->getSymbol() >=
           FIELD_TYPE_BONUS_MIN) &&
           (tiles_.at(counter_y).at(counter_x)->getSymbol() <=
           FIELD_TYPE_BONUS_MAX) &&
           (tiles_.at(counter_y).at(counter_x)->getValue() == 0))
        {
          cout << FIELD_TYPE_PATH;
        }
        else
        {
          cout << tiles_.at(counter_y).at(counter_x)->getSymbol();
        }
      }
    }
    cout << endl;
  }
  return SUCCESS;
}

//------------------------------------------------------------------------------
int Maze::showMore(bool showPath)
{
  cout << Maze::OUTPUT_REMAINING_STEPS << steps_ << endl;
  if(showPath == true)
  {
    cout << Maze::OUTPUT_MOVED_STEPS << moves_ << endl;
  }
  show();
  return SUCCESS;
}

//------------------------------------------------------------------------------
int Maze::solve(bool silent)
{
  std::vector<weight_t> min_distance;
  std::vector<vertex_t> previous;
  string solved_file_name;
  solved_file_name = filename_;
  solved_file_name.append(SOLVED_APPEND);

  //If Player has already solved the maze
  if(tiles_.at(player_.getY()).at(player_.getX())->getSymbol() ==
    FIELD_TYPE_FINISH)
  {
    throw AlreadySolvedException();
  }

  //Try to solve the maze
  if(is_adjacency_generated_ == false)
  {
    generateAdjacencyList();
    is_adjacency_generated_ = true;
  }

  // run dijkstras algorithm
  start_id_ = tiles_.at(player_.getY()).at(player_.getX())->getId();
  dijkstraComputePaths(start_id_, adjacency_list_, min_distance, previous);
  std::list<vertex_t> path = dijkstraGetShortestPathTo(finish_id_, previous);

  //If Maze is not solvable
  if(min_distance[finish_id_] == max_weight_)
  {
    throw NoPathFoundException();
  }

  solved_path_ = generatePath(path);
  solved_steps_ = min_distance[finish_id_] - ((path.size() - 1) * SOLVE_BONUS_CORRECTION);

  // solve the maze with fastmove
  if(fastMovePlayer(solved_path_) == GAME_WON)
  {
    cout << Game::OUTPUT_MAZE_SOLVED << endl;
  }

  //Save the file
  save(solved_file_name);

  //Print results
  cout << "The maze was solved in " << solved_steps_ << " steps." << endl;

  if(silent == false)
  {
    cout << "Found path: " << solved_path_ << endl;
  }

  return SUCCESS;
}

//------------------------------------------------------------------------------
void Maze::generateAdjacencyList()
{
  int counter_x = INITIALIZE_ZERO;
  int counter_y = INITIALIZE_ZERO;
  int ice_counter = INITIALIZE_ZERO;
  // Add the neighbors of every tile into the adjacency list
  for (counter_y = 1; counter_y < static_cast<int>(tiles_.size()-1);
    counter_y++)
  {
    for (counter_x = 1; counter_x <
      static_cast<int>(tiles_.at(counter_y).size()-1);
      counter_x++)
    {
      if(tiles_.at(counter_y).at(counter_x)->getSymbol() == FIELD_TYPE_WALL)
      {
        // Current tile is a wall
      }
      else
      {
        if((tiles_.at(counter_y-1).at(counter_x)->getSymbol() !=
          FIELD_TYPE_WALL) &&
          (tiles_.at(counter_y).at(counter_x)->getSymbol() !=
          FIELD_TYPE_ONEWAY_DOWN) &&
          (tiles_.at(counter_y).at(counter_x)->getSymbol() !=
          FIELD_TYPE_ONEWAY_LEFT) &&
          (tiles_.at(counter_y).at(counter_x)->getSymbol() !=
          FIELD_TYPE_ONEWAY_RIGHT))
        {
          if((tiles_.at(counter_y-1).at(counter_x)->getSymbol() >=
            FIELD_TYPE_BONUS_MIN) &&
            (tiles_.at(counter_y-1).at(counter_x)->getSymbol() <=
            FIELD_TYPE_BONUS_MAX))
          {
            adjacency_list_[tiles_.at(counter_y).at(
              counter_x)->getId()].push_back(
              neighbor(tiles_.at(counter_y-1).at(counter_x)->getId(),
              ((-1)*(tiles_.at(counter_y-1).at(counter_x)->getValue()))+ 1
              + SOLVE_BONUS_CORRECTION));
          }
          else if((tiles_.at(counter_y-1).at(counter_x)->getSymbol() >=
            FIELD_TYPE_QUICKSAND_MIN) &&
            (tiles_.at(counter_y-1).at(counter_x)->getSymbol() <=
            FIELD_TYPE_QUICKSAND_MAX))
          {
            adjacency_list_[tiles_.at(counter_y).at(
              counter_x)->getId()].push_back(
              neighbor(tiles_.at(counter_y-1).at(counter_x)->getId(),
              (tiles_.at(counter_y-1).at(counter_x)->getValue()) + 1
              + SOLVE_BONUS_CORRECTION));
          }
          else if((tiles_.at(counter_y-1).at(counter_x)->getSymbol() >=
            FIELD_TYPE_TELEPORT_MIN) &&
            (tiles_.at(counter_y-1).at(counter_x)->getSymbol() <=
            FIELD_TYPE_TELEPORT_MAX))
          {
            adjacency_list_[tiles_.at(counter_y).at(
              counter_x)->getId()].push_back(
              neighbor(getTeleportId(tiles_.at(counter_y-1).at(
              counter_x)->getSymbol(), counter_x, counter_y-1), 1
              + SOLVE_BONUS_CORRECTION));
          }
          else if(tiles_.at(counter_y-1).at(counter_x)->getSymbol() ==
            FIELD_TYPE_ICE)
          {
            ice_counter = counter_y - 1;
            while(tiles_.at(ice_counter).at(counter_x)->getSymbol() ==
              FIELD_TYPE_ICE)
            {
              ice_counter--;
            }
            if(tiles_.at(ice_counter).at(counter_x)->getSymbol() ==
              FIELD_TYPE_WALL)
            {
              ice_counter++;
            }
            if((tiles_.at(ice_counter).at(counter_x)->getSymbol() >=
              FIELD_TYPE_TELEPORT_MIN) &&
              (tiles_.at(ice_counter).at(counter_x)->getSymbol() <=
              FIELD_TYPE_TELEPORT_MAX))
            {
              adjacency_list_[tiles_.at(counter_y).at(
                counter_x)->getId()].push_back(
                neighbor(getTeleportId(tiles_.at(ice_counter).at(
                counter_x)->getSymbol(), counter_x, ice_counter),
                1 + SOLVE_BONUS_CORRECTION));
            }
            else
            {
              adjacency_list_[tiles_.at(counter_y).at(
                counter_x)->getId()].push_back(
                neighbor(tiles_.at(ice_counter).at(counter_x)->getId(),
                1 + SOLVE_BONUS_CORRECTION));
            }
          }
          else
          {
            adjacency_list_[tiles_.at(counter_y).at(
              counter_x)->getId()].push_back(
              neighbor(tiles_.at(counter_y-1).at(counter_x)->getId(),
              1 + SOLVE_BONUS_CORRECTION));
          }
        }
        if((tiles_.at(counter_y+1).at(counter_x)->getSymbol() !=
          FIELD_TYPE_WALL) &&
          (tiles_.at(counter_y).at(counter_x)->getSymbol() !=
          FIELD_TYPE_ONEWAY_UP) &&
          (tiles_.at(counter_y).at(counter_x)->getSymbol() !=
          FIELD_TYPE_ONEWAY_LEFT) &&
          (tiles_.at(counter_y).at(counter_x)->getSymbol() !=
          FIELD_TYPE_ONEWAY_RIGHT))
        {
          if((tiles_.at(counter_y+1).at(counter_x)->getSymbol() >=
            FIELD_TYPE_BONUS_MIN) &&
            (tiles_.at(counter_y+1).at(counter_x)->getSymbol() <=
            FIELD_TYPE_BONUS_MAX))
          {
            adjacency_list_[tiles_.at(counter_y).at(
              counter_x)->getId()].push_back(
              neighbor(tiles_.at(counter_y+1).at(counter_x)->getId(),
              ((-1)*(tiles_.at(counter_y+1).at(counter_x)->getValue())) + 1
              + SOLVE_BONUS_CORRECTION));
          }
          else if((tiles_.at(counter_y+1).at(counter_x)->getSymbol() >=
            FIELD_TYPE_QUICKSAND_MIN) &&
            (tiles_.at(counter_y+1).at(counter_x)->getSymbol() <=
            FIELD_TYPE_QUICKSAND_MAX))
          {
            adjacency_list_[tiles_.at(counter_y).at(
              counter_x)->getId()].push_back(
              neighbor(tiles_.at(counter_y+1).at(counter_x)->getId(),
              (tiles_.at(counter_y+1).at(counter_x)->getValue()) + 1
              + SOLVE_BONUS_CORRECTION));
          }
          else if((tiles_.at(counter_y+1).at(counter_x)->getSymbol() >=
            FIELD_TYPE_TELEPORT_MIN) &&
            (tiles_.at(counter_y+1).at(counter_x)->getSymbol() <=
            FIELD_TYPE_TELEPORT_MAX))
          {
            adjacency_list_[tiles_.at(counter_y).at(
              counter_x)->getId()].push_back(
              neighbor(getTeleportId(tiles_.at(counter_y+1).at(
              counter_x)->getSymbol(), counter_x, counter_y+1),
              1 + SOLVE_BONUS_CORRECTION));
          }
          else if(tiles_.at(counter_y+1).at(counter_x)->getSymbol() ==
            FIELD_TYPE_ICE)
          {
            ice_counter = counter_y + 1;
            while(tiles_.at(ice_counter).at(counter_x)->getSymbol() ==
              FIELD_TYPE_ICE)
            {
              ice_counter++;
            }
            if(tiles_.at(ice_counter).at(counter_x)->getSymbol() ==
              FIELD_TYPE_WALL)
            {
              ice_counter--;
            }
            if((tiles_.at(ice_counter).at(counter_x)->getSymbol() >=
              FIELD_TYPE_TELEPORT_MIN) &&
              (tiles_.at(ice_counter).at(counter_x)->getSymbol() <=
              FIELD_TYPE_TELEPORT_MAX))
            {
              adjacency_list_[tiles_.at(counter_y).at(
                counter_x)->getId()].push_back(
                neighbor(getTeleportId(tiles_.at(ice_counter).at(
                counter_x)->getSymbol(), counter_x, ice_counter),
                1 + SOLVE_BONUS_CORRECTION));
            }
            else
            {
              adjacency_list_[tiles_.at(counter_y).at(
                counter_x)->getId()].push_back(
                neighbor(tiles_.at(ice_counter).at(counter_x)->getId(),
                1 + SOLVE_BONUS_CORRECTION));
            }
          }
          else
          {
            adjacency_list_[tiles_.at(counter_y).at(
              counter_x)->getId()].push_back(
              neighbor(tiles_.at(counter_y+1).at(counter_x)->getId(),
              1 + SOLVE_BONUS_CORRECTION));
          }
        }
        if((tiles_.at(counter_y).at(counter_x-1)->getSymbol() !=
          FIELD_TYPE_WALL) &&
          (tiles_.at(counter_y).at(counter_x)->getSymbol() !=
          FIELD_TYPE_ONEWAY_DOWN) &&
          (tiles_.at(counter_y).at(counter_x)->getSymbol() !=
          FIELD_TYPE_ONEWAY_UP) &&
          (tiles_.at(counter_y).at(counter_x)->getSymbol() !=
          FIELD_TYPE_ONEWAY_RIGHT))
        {
          if((tiles_.at(counter_y).at(counter_x-1)->getSymbol() >=
            FIELD_TYPE_BONUS_MIN) &&
            (tiles_.at(counter_y).at(counter_x-1)->getSymbol() <=
            FIELD_TYPE_BONUS_MAX))
          {
            adjacency_list_[tiles_.at(counter_y).at(
              counter_x)->getId()].push_back(
              neighbor(tiles_.at(counter_y).at(counter_x-1)->getId(),
              ((-1)*(tiles_.at(counter_y).at(counter_x-1)->getValue())) + 1
              + SOLVE_BONUS_CORRECTION));
          }
          else if((tiles_.at(counter_y).at(counter_x-1)->getSymbol() >=
            FIELD_TYPE_QUICKSAND_MIN) &&
            (tiles_.at(counter_y).at(counter_x-1)->getSymbol() <=
            FIELD_TYPE_QUICKSAND_MAX))
          {
            adjacency_list_[tiles_.at(counter_y).at(
              counter_x)->getId()].push_back(
              neighbor(tiles_.at(counter_y).at(counter_x-1)->getId(),
              (tiles_.at(counter_y).at(counter_x-1)->getValue()) + 1
              + SOLVE_BONUS_CORRECTION));
          }
          else if((tiles_.at(counter_y).at(counter_x-1)->getSymbol() >=
            FIELD_TYPE_TELEPORT_MIN) &&
            (tiles_.at(counter_y).at(counter_x-1)->getSymbol() <=
            FIELD_TYPE_TELEPORT_MAX))
          {
            adjacency_list_[tiles_.at(counter_y).at(
              counter_x)->getId()].push_back(
              neighbor(getTeleportId(tiles_.at(counter_y).at(
              counter_x-1)->getSymbol(), counter_x-1, counter_y),
              1 + SOLVE_BONUS_CORRECTION));
          }
          else if(tiles_.at(counter_y).at(counter_x-1)->getSymbol() ==
            FIELD_TYPE_ICE)
          {
            ice_counter = counter_x - 1;
            while(tiles_.at(counter_y).at(ice_counter)->getSymbol() ==
              FIELD_TYPE_ICE)
            {
              ice_counter--;
            }
            if(tiles_.at(counter_y).at(ice_counter)->getSymbol() ==
              FIELD_TYPE_WALL)
            {
              ice_counter++;
            }
            if((tiles_.at(counter_y).at(ice_counter)->getSymbol() >=
              FIELD_TYPE_TELEPORT_MIN) &&
              (tiles_.at(counter_y).at(ice_counter)->getSymbol() <=
              FIELD_TYPE_TELEPORT_MAX))
            {
              adjacency_list_[tiles_.at(counter_y).at(
                counter_x)->getId()].push_back(
                neighbor(getTeleportId(tiles_.at(counter_y).at(
                ice_counter)->getSymbol(), ice_counter, counter_y),
                1 + SOLVE_BONUS_CORRECTION));
            }
            else
            {
              adjacency_list_[tiles_.at(counter_y).at(
                counter_x)->getId()].push_back(
                neighbor(tiles_.at(counter_y).at(ice_counter)->getId(),
                1 + SOLVE_BONUS_CORRECTION));
            }
          }
          else
          {
            adjacency_list_[tiles_.at(counter_y).at(
              counter_x)->getId()].push_back(
              neighbor(tiles_.at(counter_y).at(counter_x-1)->getId(),
              1 + SOLVE_BONUS_CORRECTION));
          }
        }
        if((tiles_.at(counter_y).at(counter_x+1)->getSymbol() !=
          FIELD_TYPE_WALL) &&
          (tiles_.at(counter_y).at(counter_x)->getSymbol() !=
          FIELD_TYPE_ONEWAY_DOWN) &&
          (tiles_.at(counter_y).at(counter_x)->getSymbol() !=
          FIELD_TYPE_ONEWAY_UP) &&
          (tiles_.at(counter_y).at(counter_x)->getSymbol() !=
          FIELD_TYPE_ONEWAY_LEFT))
        {
          if((tiles_.at(counter_y).at(counter_x+1)->getSymbol() >=
            FIELD_TYPE_BONUS_MIN) &&
            (tiles_.at(counter_y).at(counter_x+1)->getSymbol() <=
            FIELD_TYPE_BONUS_MAX))
          {
            adjacency_list_[tiles_.at(counter_y).at(
              counter_x)->getId()].push_back(
              neighbor(tiles_.at(counter_y).at(counter_x+1)->getId(),
              ((-1)*(tiles_.at(counter_y).at(counter_x+1)->getValue())) + 1
              + SOLVE_BONUS_CORRECTION));
          }
          else if((tiles_.at(counter_y).at(counter_x+1)->getSymbol() >=
            FIELD_TYPE_QUICKSAND_MIN) &&
            (tiles_.at(counter_y).at(counter_x+1)->getSymbol() <=
            FIELD_TYPE_QUICKSAND_MAX))
          {
            adjacency_list_[tiles_.at(counter_y).at(
              counter_x)->getId()].push_back(
              neighbor(tiles_.at(counter_y).at(counter_x+1)->getId(),
              (tiles_.at(counter_y).at(counter_x+1)->getValue()) + 1
              + SOLVE_BONUS_CORRECTION));
          }
          else if((tiles_.at(counter_y).at(counter_x+1)->getSymbol() >=
            FIELD_TYPE_TELEPORT_MIN) &&
            (tiles_.at(counter_y).at(counter_x+1)->getSymbol() <=
            FIELD_TYPE_TELEPORT_MAX))
          {
            adjacency_list_[tiles_.at(counter_y).at(
              counter_x)->getId()].push_back(
              neighbor(getTeleportId(tiles_.at(counter_y).at(
              counter_x+1)->getSymbol(), counter_x+1, counter_y),
              1 + SOLVE_BONUS_CORRECTION));
          }
          else if(tiles_.at(counter_y).at(counter_x+1)->getSymbol() ==
            FIELD_TYPE_ICE)
          {
            ice_counter = counter_x + 1;
            while(tiles_.at(counter_y).at(ice_counter)->getSymbol() ==
              FIELD_TYPE_ICE)
            {
              ice_counter++;
            }
            if(tiles_.at(counter_y).at(ice_counter)->getSymbol() ==
              FIELD_TYPE_WALL)
            {
              ice_counter--;
            }
            if((tiles_.at(counter_y).at(ice_counter)->getSymbol() >=
              FIELD_TYPE_TELEPORT_MIN) &&
              (tiles_.at(counter_y).at(ice_counter)->getSymbol() <=
              FIELD_TYPE_TELEPORT_MAX))
            {
              adjacency_list_[tiles_.at(counter_y).at(
                counter_x)->getId()].push_back(
                neighbor(getTeleportId(tiles_.at(counter_y).at(
                ice_counter)->getSymbol(), ice_counter, counter_y),
                1 + SOLVE_BONUS_CORRECTION));
            }
            else
            {
              adjacency_list_[tiles_.at(counter_y).at(
                counter_x)->getId()].push_back(
                neighbor(tiles_.at(counter_y).at(ice_counter)->getId(),
                1 + SOLVE_BONUS_CORRECTION));
            }
          }
          else
          {
            adjacency_list_[tiles_.at(counter_y).at(
              counter_x)->getId()].push_back(
              neighbor(tiles_.at(counter_y).at(counter_x+1)->getId(),
              1 + SOLVE_BONUS_CORRECTION));
          }
        }
      }
    }
  }
}

//------------------------------------------------------------------------------
string Maze::generatePath(std::list<vertex_t> path)
{
  string path_result;
  int counter_x = INITIALIZE_ZERO;
  int counter_y = INITIALIZE_ZERO;
  int ice_counter = INITIALIZE_ZERO;
  vertex_t next_id = INITIALIZE_ZERO;

  counter_x = player_.getX();
  counter_y = player_.getY();

  // pop first id because the next id is needed
  path.pop_front();
  while(!path.empty())
  {
    next_id = path.front();
    // cout << "Next ID: " << next_id << endl;
    // cout << "CX: " << counter_x << " CY" << counter_y << endl;
    path.pop_front();
    // handle teleport fields
    if((tiles_.at(counter_y-1).at(counter_x)->getSymbol() >=
      FIELD_TYPE_TELEPORT_MIN) &&
      (tiles_.at(counter_y-1).at(counter_x)->getSymbol() <=
      FIELD_TYPE_TELEPORT_MAX) &&
      (getTeleportId(tiles_.at(counter_y-1).at(counter_x)->getSymbol(),
      counter_x, counter_y-1) == next_id))
    {
      path_result.append("u");
      // cout << "U" << endl;
      for(int counter_a = 0; counter_a < (static_cast<int>(tiles_.size()));
        counter_a++)
      {
        for(int counter_b = 0;
          counter_b < (static_cast<int>(tiles_.at(counter_a).size()));
          counter_b++)
        {
          if(tiles_.at(counter_a).at(counter_b)->getId() == next_id)
          {
            counter_y = counter_a;
            counter_x = counter_b;
          }
        }
      }
      continue;

    }
    else if((tiles_.at(counter_y+1).at(counter_x)->getSymbol() >=
      FIELD_TYPE_TELEPORT_MIN) &&
      (tiles_.at(counter_y+1).at(counter_x)->getSymbol() <=
      FIELD_TYPE_TELEPORT_MAX) &&
      (getTeleportId(tiles_.at(counter_y+1).at(counter_x)->getSymbol(),
      counter_x, counter_y+1) == next_id))
    {
      path_result.append("d");
      // cout << "D" << endl;
      for(int counter_a = 0; counter_a < (static_cast<int>(tiles_.size()));
        counter_a++)
      {
        for(int counter_b = 0;
          counter_b < (static_cast<int>(tiles_.at(counter_a).size()));
          counter_b++)
        {
          if(tiles_.at(counter_a).at(counter_b)->getId() == next_id)
          {
            counter_y = counter_a;
            counter_x = counter_b;
          }
        }
      }
      continue;
    }
    else if((tiles_.at(counter_y).at(counter_x-1)->getSymbol() >=
      FIELD_TYPE_TELEPORT_MIN) &&
      (tiles_.at(counter_y).at(counter_x-1)->getSymbol() <=
      FIELD_TYPE_TELEPORT_MAX) &&
      (getTeleportId(tiles_.at(counter_y).at(counter_x-1)->getSymbol(),
      counter_x-1, counter_y) == next_id))
    {
      path_result.append("l");
      // cout << "L" << endl;
      for(int counter_a = 0; counter_a < (static_cast<int>(tiles_.size()));
        counter_a++)
      {
        for(int counter_b = 0;
          counter_b < (static_cast<int>(tiles_.at(counter_a).size()));
          counter_b++)
        {
          if(tiles_.at(counter_a).at(counter_b)->getId() == next_id)
          {
            counter_y = counter_a;
            counter_x = counter_b;
          }
        }
      }
      continue;
    }
    else if((tiles_.at(counter_y).at(counter_x+1)->getSymbol() >=
      FIELD_TYPE_TELEPORT_MIN) &&
      (tiles_.at(counter_y).at(counter_x+1)->getSymbol() <=
      FIELD_TYPE_TELEPORT_MAX) &&
      (getTeleportId(tiles_.at(counter_y).at(counter_x+1)->getSymbol(),
      counter_x+1, counter_y) == next_id))
    {
      path_result.append("r");
      // cout << "R" << endl;
      for(int counter_a = 0; counter_a < (static_cast<int>(tiles_.size()));
        counter_a++)
      {
        for(int counter_b = 0;
          counter_b < (static_cast<int>(tiles_.at(counter_a).size()));
          counter_b++)
        {
          if(tiles_.at(counter_a).at(counter_b)->getId() == next_id)
          {
            counter_y = counter_a;
            counter_x = counter_b;
          }
        }
      }
      continue;
    }

    // handle the other fields
    if(tiles_.at(counter_y-1).at(counter_x)->getId() == next_id)
    {
      path_result.append("u");
      // cout << "u" << endl;
      counter_y--;
    }
    else if(tiles_.at(counter_y+1).at(counter_x)->getId() == next_id)
    {
      path_result.append("d");
      // cout << "d" << endl;
      counter_y++;
    }
    else if(tiles_.at(counter_y).at(counter_x-1)->getId() == next_id)
    {
      path_result.append("l");
      // cout << "l" << endl;
      counter_x--;
    }
    else if(tiles_.at(counter_y).at(counter_x+1)->getId() == next_id)
    {
      path_result.append("r");
      // cout << "r" << endl;
      counter_x++;
    }
    else
    {
      if(tiles_.at(counter_y-1).at(counter_x)->getSymbol() == FIELD_TYPE_ICE)
      {
        ice_counter = counter_y - 1;
        while(tiles_.at(ice_counter).at(counter_x)->getSymbol() ==
          FIELD_TYPE_ICE)
        {
          ice_counter--;
        }
        if(tiles_.at(ice_counter).at(counter_x)->getSymbol() ==
          FIELD_TYPE_WALL)
        {
          ice_counter++;
        }
        if((tiles_.at(ice_counter).at(counter_x)->getId() == next_id) ||
          (getTeleportId(tiles_.at(ice_counter).at(counter_x)->getSymbol(),
          counter_x, ice_counter) == next_id))
        {
          counter_y = ice_counter;
          path_result.append("u");
          for(int counter_a = 0; counter_a < (static_cast<int>(tiles_.size()));
            counter_a++)
          {
            for(int counter_b = 0;
              counter_b < (static_cast<int>(tiles_.at(counter_a).size()));
              counter_b++)
            {
              if(tiles_.at(counter_a).at(counter_b)->getId() == next_id)
              {
                counter_y = counter_a;
                counter_x = counter_b;
              }
            }
          }
        }
      }
      if(tiles_.at(counter_y+1).at(counter_x)->getSymbol() == FIELD_TYPE_ICE)
      {
        ice_counter = counter_y + 1;
        while(tiles_.at(ice_counter).at(counter_x)->getSymbol() ==
          FIELD_TYPE_ICE)
        {
          ice_counter++;
        }
        if(tiles_.at(ice_counter).at(counter_x)->getSymbol() ==
          FIELD_TYPE_WALL)
        {
          ice_counter--;
        }
        if((tiles_.at(ice_counter).at(counter_x)->getId() == next_id) ||
          (getTeleportId(tiles_.at(ice_counter).at(counter_x)->getSymbol(),
          counter_x, ice_counter) == next_id))
        {
          counter_y = ice_counter;
          path_result.append("d");
          for(int counter_a = 0;
            counter_a < (static_cast<int>(tiles_.size())); counter_a++)
          {
            for(int counter_b = 0;
              counter_b < (static_cast<int>(tiles_.at(counter_a).size()));
              counter_b++)
            {
              if(tiles_.at(counter_a).at(counter_b)->getId() == next_id)
              {
                counter_y = counter_a;
                counter_x = counter_b;
              }
            }
          }
        }
      }
      if(tiles_.at(counter_y).at(counter_x-1)->getSymbol() == FIELD_TYPE_ICE)
      {
        ice_counter = counter_x - 1;
        while(tiles_.at(counter_y).at(ice_counter)->getSymbol() ==
          FIELD_TYPE_ICE)
        {
          ice_counter--;
        }
        if(tiles_.at(counter_y).at(ice_counter)->getSymbol() ==
          FIELD_TYPE_WALL)
        {
          ice_counter++;
        }
        if((tiles_.at(counter_y).at(ice_counter)->getId() == next_id) ||
          (getTeleportId(tiles_.at(counter_y).at(ice_counter)->getSymbol(),
          ice_counter, counter_y) == next_id))
        {
          counter_y = ice_counter;
          path_result.append("l");
          for(int counter_a = 0; counter_a < (static_cast<int>(tiles_.size()));
            counter_a++)
          {
            for(int counter_b = 0;
              counter_b < (static_cast<int>(tiles_.at(counter_a).size()));
              counter_b++)
            {
              if(tiles_.at(counter_a).at(counter_b)->getId() == next_id)
              {
                counter_y = counter_a;
                counter_x = counter_b;
              }
            }
          }
        }
      }
      if(tiles_.at(counter_y).at(counter_x+1)->getSymbol() == FIELD_TYPE_ICE)
      {
        ice_counter = counter_x + 1;
        while(tiles_.at(counter_y).at(ice_counter)->getSymbol() ==
          FIELD_TYPE_ICE)
        {
          ice_counter++;
        }
        if(tiles_.at(counter_y).at(ice_counter)->getSymbol() ==
          FIELD_TYPE_WALL)
        {
          ice_counter--;
        }
        if((tiles_.at(counter_y).at(ice_counter)->getId() == next_id) ||
          (getTeleportId(tiles_.at(counter_y).at(ice_counter)->getSymbol(),
          ice_counter, counter_y) == next_id))
        {
          counter_y = ice_counter;
          path_result.append("r");
          for(int counter_a = 0; counter_a < (static_cast<int>(tiles_.size()));
            counter_a++)
          {
            for(int counter_b = 0;
              counter_b < (static_cast<int>(tiles_.at(counter_a).size()));
              counter_b++)
            {
              if(tiles_.at(counter_a).at(counter_b)->getId() == next_id)
              {
                counter_y = counter_a;
                counter_x = counter_b;
              }
            }
          }
        }
      }
    }
  }

  return path_result;
}

//------------------------------------------------------------------------------
int Maze::resetAdjacencyList()
{
  adjacency_list_.clear();

  return SUCCESS;
}

//------------------------------------------------------------------------------
int Maze::movePlayer(string direction)
{
  bool fastmove = false;
  bool ice = false;

  // Set Fastmove or Ice
  if(direction.back() == FAST_MOVE_FLAG)
  {
    direction.pop_back();
    fastmove = true;
  }
  else if(direction.back() == ICE_MOVE_FLAG)
  {
    direction.pop_back();
    ice = true;
  }

  if((fastmove == false) &&
    (player_.getTile() == FIELD_TYPE_FINISH))
  {
    throw InvalidMoveException();
  }

  if(ice == false)
  {
    if(steps_ <= 0)
    {
      steps_ = INITIALIZE_ZERO;
      if(fastmove)
      {
        return OUT_OF_STEPS;
      }
      else
      {
        cout << steps_ << endl;
        throw NoMoreStepsException();
      }
    }
  }

  // Check if move is valid
  if(tiles_.at(player_.getY()).at(player_.getX())->move(direction) == false)
  {
    return INVALID_MOVE;
  }

  // delete Bonus Tile
  if((player_.getTile() >= FIELD_TYPE_BONUS_MIN) &&
    (player_.getTile() <= FIELD_TYPE_BONUS_MAX))
  {
    tiles_.at(player_.getY()).at(player_.getX())->setValue(0);
  }

  // change counter to wall if the symbol is zero

  if((player_.getTile() >= FIELD_TYPE_COUNTER_MIN) &&
    (player_.getTile() <= FIELD_TYPE_COUNTER_MAX) &&
    (tiles_.at(player_.getY()).at(player_.getX())->getSymbol() != FIELD_TYPE_WALL))
  {
    tiles_.at(player_.getY()).at(player_.getX())->setSymbol(tiles_.at(player_.getY()).at(player_.getX())->getSymbol() - 1);
  }
  if((tiles_.at(player_.getY()).at(player_.getX())->getSymbol() - COUNTER_ZERO_CHAR) == INITIALIZE_ZERO)
  {
    tiles_.at(player_.getY()).at(player_.getX())->setSymbol(FIELD_TYPE_WALL);
  }

  // Move the player and count down
  if(direction == Game::DIRECTION_MOVE_UP)
  {
    if(tiles_.at(player_.getY() - 1).at(player_.getX())->getSymbol() !=
      FIELD_TYPE_WALL)
    {
      player_.setY(player_.getY() - 1);
      if(ice == false)
      {
        steps_--;
        if(fastmove == false)
        {
          moves_ += Game::DIRECTION_FAST_MOVE_UP;
        }
      }
    }
    else
    {
      if(ice)
      {
        return SUCCESS;
      }
      else
      {
        return INVALID_MOVE;
      }
    }
  }
  else if(direction == Game::DIRECTION_MOVE_DOWN)
  {
    if(tiles_.at(player_.getY() + 1).at(player_.getX())->getSymbol() !=
      FIELD_TYPE_WALL)
    {
      player_.setY(player_.getY() + 1);
      if(ice == false)
      {
        steps_--;
        if(fastmove == false)
        {
          moves_ += Game::DIRECTION_FAST_MOVE_DOWN;
        }
      }
    }
    else
    {
      if(ice)
      {
        return SUCCESS;
      }
      else
      {
        return INVALID_MOVE;
      }
    }
  }
  else if(direction == Game::DIRECTION_MOVE_LEFT)
  {
    if(tiles_.at(player_.getY()).at(player_.getX() - 1)->getSymbol() !=
      FIELD_TYPE_WALL)
    {
      player_.setX(player_.getX() - 1);
      if(ice == false)
      {
        steps_--;
        if(fastmove == false)
        {
          moves_ += Game::DIRECTION_FAST_MOVE_LEFT;
        }
      }
    }
    else
    {
      if(ice)
      {
        return SUCCESS;
      }
      else
      {
        return INVALID_MOVE;
      }
    }
  }
  else if(direction == Game::DIRECTION_MOVE_RIGHT)
  {
    if(tiles_.at(player_.getY()).at(player_.getX() + 1)->getSymbol() !=
      FIELD_TYPE_WALL)
    {
      player_.setX(player_.getX() + 1);
      if(ice == false)
      {
        steps_--;
        if(fastmove == false)
        {
          moves_ += Game::DIRECTION_FAST_MOVE_RIGHT;
        }
      }
    }
    else
    {
      if(ice)
      {
        return SUCCESS;
      }
      else
      {
        return INVALID_MOVE;
      }
    }
  }

  player_.setTile(getTile(player_.getX(), player_.getY()));

  // Player lands on Teleport tile
  if((player_.getTile() >= FIELD_TYPE_TELEPORT_MIN) &&
    (player_.getTile() <= FIELD_TYPE_TELEPORT_MAX))
  {
    player_.setTile(getTile(player_.getX(), player_.getY()));
    moveTeleport(player_.getTile());
  }

  // Player lands on Bonus tile
  if((player_.getTile() >= FIELD_TYPE_BONUS_MIN) &&
    (player_.getTile() <= FIELD_TYPE_BONUS_MAX))
  {
    steps_ = steps_ + tiles_.at(player_.getY()).at(player_.getX())->getValue();
  }

  // Player lands on Quicksand
  if((player_.getTile() >= FIELD_TYPE_QUICKSAND_MIN) &&
    (player_.getTile() <= FIELD_TYPE_QUICKSAND_MAX))
  {
    steps_ = steps_ - tiles_.at(player_.getY()).at(player_.getX())->getValue();
    // Set steps_ to zero if it is less than zero
    if(steps_ < 0)
    {
      steps_ = INITIALIZE_ZERO;
    }
  }

  // Player lands on Hole tile
  if(player_.getTile() == FIELD_TYPE_HOLE)
  {
    moveTeleport(FIELD_TYPE_START);
  }

  // Player lands on Ice
  if((player_.getTile()) == FIELD_TYPE_ICE)
  {
    movePlayer(direction + ICE_MOVE_FLAG);
  }
  if((fastmove == false) &&
    (player_.getTile() == FIELD_TYPE_FINISH))
  {
    return GAME_WON;
  }

  return SUCCESS;
}

//------------------------------------------------------------------------------
int Maze::fastMovePlayer(string directions)
{
  string moves_save = moves_;
  unsigned int counter_string = INITIALIZE_ZERO;
  int return_value = INITIALIZE_ZERO;

  if(player_.getTile() == FIELD_TYPE_FINISH)
  {
    throw InvalidMoveException();
  }

  while(counter_string<directions.size())
  {
    if(directions.at(counter_string) == Game::DIRECTION_FAST_MOVE_UP)
    {
      return_value = movePlayer(Game::DIRECTION_MOVE_UP +
        Maze::FAST_MOVE_FLAG);
    }
    else if(directions.at(counter_string) == Game::DIRECTION_FAST_MOVE_DOWN)
    {
      return_value = movePlayer(Game::DIRECTION_MOVE_DOWN +
        Maze::FAST_MOVE_FLAG);
    }
    else if(directions.at(counter_string) == Game::DIRECTION_FAST_MOVE_LEFT)
    {
      return_value = movePlayer(Game::DIRECTION_MOVE_LEFT +
        Maze::FAST_MOVE_FLAG);
    }
    else if(directions.at(counter_string) == Game::DIRECTION_FAST_MOVE_RIGHT)
    {
      return_value = movePlayer(Game::DIRECTION_MOVE_RIGHT +
        Maze::FAST_MOVE_FLAG);
    }
    else
    {
      return_value = INVALID_MOVE;
    }
    counter_string++;

    if((return_value != SUCCESS) &&
      (return_value != GAME_WON))
    {
      moves_save = moves_;
      load(SAVE_FILE_NAME);
      fastMovePlayer(moves_save);

      if(return_value != SUCCESS)
      {
        throw InvalidMoveException();
      }
    }
  }
  moves_ += directions;

  if(player_.getTile() == FIELD_TYPE_FINISH)
  {
    return GAME_WON;
  }
  return return_value;
}

//------------------------------------------------------------------------------
int Maze::fastMovePlayerLoad(string directions)
{
  string moves_save = moves_;
  unsigned int counter_string = INITIALIZE_ZERO;
  int return_value = INITIALIZE_ZERO;

  if(player_.getTile() == FIELD_TYPE_FINISH)
  {
    throw InvalidMoveException();
  }

  while(counter_string<directions.size())
  {
    if(directions.at(counter_string) == Game::DIRECTION_FAST_MOVE_UP)
    {
      return_value = movePlayer(Game::DIRECTION_MOVE_UP +
        Maze::FAST_MOVE_FLAG);
    }
    else if(directions.at(counter_string) == Game::DIRECTION_FAST_MOVE_DOWN)
    {
      return_value = movePlayer(Game::DIRECTION_MOVE_DOWN +
        Maze::FAST_MOVE_FLAG);
    }
    else if(directions.at(counter_string) == Game::DIRECTION_FAST_MOVE_LEFT)
    {
      return_value = movePlayer(Game::DIRECTION_MOVE_LEFT +
        Maze::FAST_MOVE_FLAG);
    }
    else if(directions.at(counter_string) == Game::DIRECTION_FAST_MOVE_RIGHT)
    {
      return_value = movePlayer(Game::DIRECTION_MOVE_RIGHT +
        Maze::FAST_MOVE_FLAG);
    }
    else
    {
      return_value = INVALID_MOVE;
    }
    counter_string++;

    if((return_value != SUCCESS) &&
       (return_value != GAME_WON))
    {
      moves_save = moves_;
      load(SAVE_FILE_NAME);
      fastMovePlayerLoad(moves_save);
      if(return_value != SUCCESS)
      {
        throw InvalidPathException();
      }
    }
  }
  moves_ += directions;

  if(player_.getTile() == FIELD_TYPE_FINISH)
  {
    return GAME_WON;
  }
  return return_value;
}

//------------------------------------------------------------------------------
int Maze::moveTeleport(char symbol)
{
  int counter_x = INITIALIZE_ZERO;
  int counter_y = INITIALIZE_ZERO;
  for(counter_y = 0; counter_y < static_cast<int>(tiles_.size());
    counter_y++)
  {
    for(counter_x = 0;
      counter_x < static_cast<int>(tiles_.at(counter_y).size());
      counter_x++)
    {
      if((tiles_.at(counter_y).at(counter_x)->getSymbol() == symbol) &&
        ((counter_y != player_.getY()) || (counter_x != player_.getX())))
      {
        player_.setY(counter_y);
        player_.setX(counter_x);
        player_.setTile(getTile(counter_x, counter_y));
        return 0;
      }
    }
  }
  return ERROR;
}

//------------------------------------------------------------------------------
int Maze::getTeleportId(char symbol, int cur_x, int cur_y)
{
  int counter_x = INITIALIZE_ZERO;
  int counter_y = INITIALIZE_ZERO;
  for(counter_y = 0; counter_y < static_cast<int>(tiles_.size());
    counter_y++)
  {
    for(counter_x = 0;
      counter_x < static_cast<int>(tiles_.at(counter_y).size());
      counter_x++)
    {
      if((tiles_.at(counter_y).at(counter_x)->getSymbol() == symbol) &&
        ((counter_y != cur_y) || (counter_x != cur_x)))
      {
        return tiles_.at(counter_y).at(counter_x)->getId();
      }
    }
  }
  return ERROR;
}

//------------------------------------------------------------------------------
int Maze::deleteMaze()
{
  int counter_x = INITIALIZE_ZERO;
  int counter_y = INITIALIZE_ZERO;
  for(counter_y = static_cast<int>(tiles_.size())-1; counter_y >= 0;
    counter_y--)
  {
    for(counter_x = static_cast<int>(tiles_.at(counter_y).size()) - 1;
      counter_x >= 0; counter_x--)
    {
      tiles_.at(counter_y).at(counter_x).reset();
    }
    tiles_.at(counter_y).clear();
  }
  tiles_.clear();

  return SUCCESS;
}

//------------------------------------------------------------------------------
char Maze::getTile(int x, int y)
{
  return tiles_.at(y).at(x)->getSymbol();
}

//------------------------------------------------------------------------------
Player* Maze::getPlayer()
{
  return &player_;
}

//------------------------------------------------------------------------------
int Maze::getPlayerX()
{
  return player_.getX();
}

//------------------------------------------------------------------------------
void Maze::setPlayerX(int x)
{
  player_.setX(x);
}

//------------------------------------------------------------------------------
int Maze::getPlayerY()
{
  return player_.getY();
}

//------------------------------------------------------------------------------
void Maze::setPlayerY(int y)
{
  player_.setY(y);
}

//------------------------------------------------------------------------------
bool Maze::isFilenameValid(string filename)
{
  int filename_counter = INITIALIZE_ZERO;
  for(char& filename_letter : filename)
  {
    if(filename_counter == FILENAME_MAX_SIZE)
    {
      return false;
    }
    if((filename_letter >= FILENAME_DEFINITION_LOWERCASE_MIN &&
      filename_letter <= FILENAME_DEFINITION_LOWERCASE_MAX) ||
      (filename_letter >= FILENAME_DEFINITION_UPPERCASE_MIN &&
      filename_letter <= FILENAME_DEFINITION_UPPERCASE_MAX) ||
      (filename_letter >= FILENAME_DEFINITION_NUMBER_MIN &&
      filename_letter <= FILENAME_DEFINITION_NUMBER_MAX) ||
      filename_letter == FILENAME_DEFINITION_DOT ||
      filename_letter == FILENAME_DEFINITION_SLASH)
    {
      filename_counter++;
    }
    else
    {
      return false;
    }
  }
  return true;
}


