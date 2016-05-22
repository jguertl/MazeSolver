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

//------------------------------------------------------------------------------
Maze::Maze() : steps_(0)
{
}

//------------------------------------------------------------------------------
Maze::~Maze()
{
}

//------------------------------------------------------------------------------
int Maze::load(const string& path)
{
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
  counter_x_ = INITIALIZE_ZERO;
  counter_y_ = INITIALIZE_ZERO;

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

    counter_x_ = INITIALIZE_ZERO;
    counter_y_ = INITIALIZE_ZERO;
    // Check if moves are valid
    while(counter_x_ < (static_cast<int>(moves_.size())))
    {
      if((moves_.at(counter_x_) != Game::DIRECTION_FAST_MOVE_UP) &&
        (moves_.at(counter_x_) != Game::DIRECTION_FAST_MOVE_DOWN) &&
        (moves_.at(counter_x_) != Game::DIRECTION_FAST_MOVE_LEFT) &&
        (moves_.at(counter_x_) != Game::DIRECTION_FAST_MOVE_RIGHT))
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
      counter_x_++;
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

    counter_x_ = INITIALIZE_ZERO;
    while(file.get(buffer))
    {
      // Store the buffer to check if the last char is a linebreak
      buffer_check = buffer;

      if(buffer == FIELD_TYPE_WALL)
      {
        // Wall
        unique_buffer = unique_ptr<Tile>(new Wall(buffer));
        unique_vector_buffer.push_back(move(unique_buffer));
      }
      else if(buffer == FIELD_TYPE_PATH)
      {
        // Path
        unique_buffer = unique_ptr<Tile>(new Path(buffer));
        unique_vector_buffer.push_back(move(unique_buffer));
      }
      else if(buffer == FIELD_TYPE_ICE)
      {
        // Ice
        unique_buffer = unique_ptr<Tile>(new Ice(buffer));
        unique_vector_buffer.push_back(move(unique_buffer));
      }
      else if(buffer == FIELD_TYPE_START)
      {
        // Start
        unique_buffer = unique_ptr<Tile>(new Start(buffer));
        unique_vector_buffer.push_back(move(unique_buffer));
        player_.setX(counter_x_);
        player_.setY(counter_y_);
        start_check++;
      }
      else if(buffer == FIELD_TYPE_FINISH)
      {
        // Finish
        unique_buffer = unique_ptr<Tile>(new Finish(buffer));
        unique_vector_buffer.push_back(move(unique_buffer));
        finish_check++;
      }
      else if((buffer >= FIELD_TYPE_BONUS_MIN) &&
        (buffer <= FIELD_TYPE_BONUS_MAX))
      {
        // Bonus
        unique_buffer = unique_ptr<Tile>(new Bonus(buffer,
          (buffer - FIELD_TYPE_BONUS_MIN + BONUS_OFFSET)));
        unique_vector_buffer.push_back(move(unique_buffer));
      }
      else if((buffer >= FIELD_TYPE_QUICKSAND_MIN) &&
        (buffer <= FIELD_TYPE_QUICKSAND_MAX))
      {
        // Quicksand
        unique_buffer = unique_ptr<Tile>(new Quicksand(buffer));
        unique_vector_buffer.push_back(move(unique_buffer));
      }
      else if((buffer >= FIELD_TYPE_TELEPORT_MIN) &&
        (buffer <= FIELD_TYPE_TELEPORT_MAX))
      {
        // Teleport
        unique_buffer = unique_ptr<Tile>(new Teleport(buffer));
        unique_vector_buffer.push_back(move(unique_buffer));

        teleport_symbols.push_back(buffer);
      }
      else if(buffer == FIELD_TYPE_HOLE)
      {
        // Hole
        unique_buffer = unique_ptr<Tile>(new Hole(buffer));
        unique_vector_buffer.push_back(move(unique_buffer));
      }
      else if((buffer >= FIELD_TYPE_COUNTER_MIN) &&
              (buffer <= FIELD_TYPE_COUNTER_MAX))
      {
        // Counter
        unique_buffer = unique_ptr<Tile>(new Counter(buffer));
        unique_vector_buffer.push_back(move(unique_buffer));
      }
      else if((buffer == FIELD_TYPE_ONEWAY_LEFT) ||
        (buffer == FIELD_TYPE_ONEWAY_RIGHT) ||
        (buffer == FIELD_TYPE_ONEWAY_UP) ||
        (buffer == FIELD_TYPE_ONEWAY_DOWN))
      {
        // OneWay
        unique_buffer = unique_ptr<Tile>(new OneWay(buffer));
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

      counter_x_++;
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
        counter_y_++;
        counter_x_ = INITIALIZE_ZERO;
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
    for(counter_x_ = 0; counter_x_ < static_cast<int>(tiles_.front().size());
      counter_x_++)
    {
      if((tiles_.front().at(counter_x_)->getSymbol()) != FIELD_TYPE_WALL)
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
    counter_x_ = INITIALIZE_ZERO;
    for(counter_x_ = 0; counter_x_ < static_cast<int>(tiles_.back().size());
      counter_x_++)
    {

      if((tiles_.back().at(counter_x_)->getSymbol()) != FIELD_TYPE_WALL)
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
    throw FileOpenException();
  }
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

  for (counter_y_ = 0; counter_y_ < static_cast<int>(tiles_.size());
    counter_y_++)
  {
    for (counter_x_ = 0;
      counter_x_ < static_cast<int>(tiles_.at(counter_y_).size());
      counter_x_++)
    {
      outputfile << tiles_.at(counter_y_).at(counter_x_)->getSymbol();
    }
    outputfile << endl;
  }
  outputfile.close();
  return SUCCESS;
}

//------------------------------------------------------------------------------
int Maze::show()
{
  for (counter_y_ = 0; counter_y_ < static_cast<int>(tiles_.size());
    counter_y_++)
  {
    for (counter_x_ = 0; counter_x_ <
      static_cast<int>(tiles_.at(counter_y_).size());
      counter_x_++)
    {
      if((counter_y_ == player_.getY()) && (counter_x_ == player_.getX()))
      {
        cout << FIELD_TYPE_PLAYER;
      }
      else
      {
        if((tiles_.at(counter_y_).at(counter_x_)->getSymbol() >=
           FIELD_TYPE_BONUS_MIN) &&
           (tiles_.at(counter_y_).at(counter_x_)->getSymbol() <=
           FIELD_TYPE_BONUS_MAX) &&
           (tiles_.at(counter_y_).at(counter_x_)->getValue() == 0))
        {
          cout << FIELD_TYPE_PATH;
        }
        else
        {
          cout << tiles_.at(counter_y_).at(counter_x_)->getSymbol();
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
  //Try to solve the maze

  //If Maze is not solvable
  throw NoPathFoundException();

  //If Player has already solved the maze
  throw AlreadySolvedException();

  //Solve the maze using fastmove

  //Save the file

  //Print results
  cout << "The maze was solved in " << "7" << " steps." << endl;

  if(silent == false)
  {
    cout << "Found path: " << "llldr" << endl;
  }

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
    steps_ = steps_- ((player_.getTile() -
      FIELD_TYPE_QUICKSAND_MIN) + QUICKSAND_OFFSET);
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
  for(counter_y_ = 0; counter_y_ < static_cast<int>(tiles_.size());
    counter_y_++)
  {
    for(counter_x_ = 0;
      counter_x_ < static_cast<int>(tiles_.at(counter_y_).size());
      counter_x_++)
    {
      if((tiles_.at(counter_y_).at(counter_x_)->getSymbol() == symbol) &&
        ((counter_y_ != player_.getY()) || (counter_x_ != player_.getX())))
      {
        player_.setY(counter_y_);
        player_.setX(counter_x_);
        player_.setTile(getTile(counter_x_, counter_y_));
        return 0;
      }
    }
  }
  return ERROR;
}

//------------------------------------------------------------------------------
int Maze::deleteMaze()
{

  for(counter_y_ = static_cast<int>(tiles_.size())-1; counter_y_ >= 0;
    counter_y_--)
  {
    for(counter_x_ = static_cast<int>(tiles_.at(counter_y_).size()) - 1;
      counter_x_ >= 0; counter_x_--)
    {
      tiles_.at(counter_y_).at(counter_x_).reset();
    }
    tiles_.at(counter_y_).clear();
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


