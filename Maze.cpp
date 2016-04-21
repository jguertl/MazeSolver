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
#include "Maze.h"
#include "Game.h"
#include "FileOpenException.h"

using std::ofstream;
using std::ifstream;
using std::string;
using std::cout;
using std::endl;

const string Maze::OUTPUT_REMAINING_STEPS = "Remaining Steps: ";
const string Maze::OUTPUT_MOVED_STEPS = "Moved Steps: ";
const string Maze::OUTPUT_MAZE_SOLVED = "Congratulation! You solved the maze.";
const string Maze::SAVE_FILE_NAME = "save_file.txt";
const char Maze::FAST_MOVE_FLAG = 'f';
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
const char Maze::FILENAME_DEFINITION_LOWERCASE_MIN = 'a';
const char Maze::FILENAME_DEFINITION_LOWERCASE_MAX = 'z';
const char Maze::FILENAME_DEFINITION_UPPERCASE_MIN = 'A';
const char Maze::FILENAME_DEFINITION_UPPERCASE_MAX = 'Z';
const char Maze::FILENAME_DEFINITION_NUMBER_MIN = '0';
const char Maze::FILENAME_DEFINITION_NUMBER_MAX = '9';
const char Maze::FILENAME_DEFINITION_DOT = '.';
const char Maze::FILENAME_DEFINITION_SLASH = '/';

//------------------------------------------------------------------------------
Maze::Maze()
{
  steps_ = 0;
}

//------------------------------------------------------------------------------
Maze::~Maze()
{
}

//------------------------------------------------------------------------------
void Maze::load(const string& path)
{
  cout << "Load from " << path << endl;
  if(isFilenameValid(path)!=0)
  {
    cout << "Filename not valid." << endl;
    return;
  }
  ifstream file ("maze.txt");
  string line;
  char buffer;
  vector<Tile*> buffer_vector;
  vector<char> teleport_symbols;
  std::stringstream sstream;
  int size_check = -1;
  counter_x_ = 0;
  counter_y_ = 0;
  if (file.is_open())
  {
    std::getline(file, moves_);
    std::getline(file, line);
    sstream<<line;
    sstream>>original_steps_;
    steps_ = original_steps_;
    sstream.str("");
    sstream.clear();

    while(file.get(buffer))
    {
      //TODO make switch case
      if(buffer == FIELD_TYPE_WALL)
      {
        // Wall
        buffer_vector.push_back(new Wall(buffer));
      }
      else if(buffer== FIELD_TYPE_PATH)
      {
        // Path
        buffer_vector.push_back(new Path(buffer));
      }
      else if(buffer== FIELD_TYPE_ICE)
      {
        // Ice
        buffer_vector.push_back(new Ice(buffer));
      }
      else if(buffer==FIELD_TYPE_START)
      {
        // Start
        buffer_vector.push_back(new Start(buffer));
        player_.setX(counter_x_);
        player_.setY(counter_y_);
      }
      else if(buffer==FIELD_TYPE_FINISH)
      {
        // Finish
        buffer_vector.push_back(new Finish(buffer));
      }
      else if(buffer>=FIELD_TYPE_BONUS_MIN && buffer<=FIELD_TYPE_BONUS_MAX)
      {
        // Bonus
        buffer_vector.push_back(new Bonus(buffer));
      }
      else if(buffer>=FIELD_TYPE_QUICKSAND_MIN && buffer<=FIELD_TYPE_QUICKSAND_MAX)
      {
        // Quicksand
        buffer_vector.push_back(new Quicksand(buffer));
      }
      else if(buffer>=FIELD_TYPE_TELEPORT_MIN && buffer<=FIELD_TYPE_TELEPORT_MAX)
      {
        // Teleport
        buffer_vector.push_back(new Teleport(buffer));

        teleport_symbols.push_back(buffer);
      }
      else if(buffer==FIELD_TYPE_ONEWAY_LEFT ||
              buffer==FIELD_TYPE_ONEWAY_RIGHT ||
              buffer==FIELD_TYPE_ONEWAY_UP ||
              buffer==FIELD_TYPE_ONEWAY_DOWN)
      {
        // OneWay
        buffer_vector.push_back(new OneWay(buffer));
      }else if(buffer != '\n')
      {
        cout << "Input File not valid  A" << endl;
      }

      counter_x_++;
      if(buffer=='\n')
      {
        tiles_.push_back(buffer_vector);

        // Check Maze
        if((size_check >= 0) && (size_check != buffer_vector.size()))
        {
          cout << "Input File not valid  B" << endl;
        }
        if((buffer_vector.front()->getSymbol() != FIELD_TYPE_WALL) &&
           (buffer_vector.at(buffer_vector.size()-1)->getSymbol() != FIELD_TYPE_WALL))
        {
          cout << "Input File not valid  C" << endl;
        }

        size_check = buffer_vector.size();
        buffer_vector.clear();
        counter_y_++;
        counter_x_=0;
      }
    }
    // Check if first line only contains Walls
    for(counter_x_=0; counter_x_<tiles_.back().size(); counter_x_++)
    {
      if(tiles_.front().at(counter_x_)->getSymbol() != FIELD_TYPE_WALL)
      {
        cout << "Input File not valid  D" << endl;
      }
    }
    // Check if last line only contains Walls
    for(counter_x_=0; counter_x_<tiles_.back().size(); counter_x_++)
    {
      if(tiles_.back().at(counter_x_)->getSymbol() != FIELD_TYPE_WALL)
      {
        cout << "Input File not valid  E" << endl;
      }
    }

    // Check all Teleports
    sort(teleport_symbols.begin(), teleport_symbols.end());
    while(teleport_symbols.size()>1)
    {
      buffer = teleport_symbols.back();
      teleport_symbols.pop_back();
      if(buffer != teleport_symbols.back())
      {
        cout << "Teleport Error 1" << endl;
        return;
      }
      teleport_symbols.pop_back();

    }
    if(teleport_symbols.size()!=0)
    {
      cout << "Teleport Error 2" << endl;
      return;
    }

    player_.setTile(tiles_.at(player_.getY()).at(player_.getX()));
    file.close();
    save(SAVE_FILE_NAME);
    fastMovePlayer(moves_);
  }
  else
  {
    cout << "Unable to open file";
  }

}

//------------------------------------------------------------------------------
// Einige Angaben sind mir nicht ganz klar.
void Maze::save(const string& path)
{
  ofstream outputfile;
  if(isFilenameValid(path)!=0)
  {
    cout << "Filename not valid." << endl;
    return;
  }
  outputfile.open(path.c_str());

  if(path == SAVE_FILE_NAME)
  {
    outputfile << endl;
  }
  else
  {
    outputfile << moves_ << endl;
  }

  outputfile << original_steps_ << endl;

  for (counter_x_ = 0; counter_x_ < tiles_.size(); counter_x_++)
  {
    for (counter_y_ = 0; counter_y_ < tiles_.at(counter_x_).size(); counter_y_++)
    {
      outputfile << tiles_.at(counter_x_).at(counter_y_)->getSymbol();
    }
    outputfile << endl;
  }

  outputfile.close();
}

//------------------------------------------------------------------------------
void Maze::show()
{
  for (counter_x_ = 0; counter_y_ < tiles_.size(); counter_x_++)
  {
    for (counter_y_ = 0; counter_y_ < tiles_.at(counter_x_).size(); counter_y_++)
    {
      if((counter_x_ == player_.getY()) && (counter_y_ == player_.getX()))
      {
        cout << FIELD_TYPE_PLAYER;
      }
      else
      {
        cout << tiles_.at(counter_x_).at(counter_y_)->getSymbol();
      }
    }
    cout << endl;
  }
}

//------------------------------------------------------------------------------
void Maze::showMore()
{
  cout << Maze::OUTPUT_REMAINING_STEPS << steps_ << endl;
  cout << Maze::OUTPUT_MOVED_STEPS << moves_ << endl;
  show();
}

//------------------------------------------------------------------------------
int Maze::movePlayer(string direction)
{
  // check if move is in a valid direction
  if(player_.getTile()->move(direction) == false)
  {
    cout << "[ERR] Invalid move." << endl;
    return -1;
  }

  if(direction.back()==FAST_MOVE_FLAG)
  {
    direction.pop_back();
  }
  else
  {
    if(player_.getTile()->getSymbol()=='x')
    {
      cout << "Game is over." << endl;
      return -2;
    }
  }

  // delete Bonus Tile
  if((player_.getTile()->getSymbol()>='a') &&
     (player_.getTile()->getSymbol()<='e'))
  {
    delete tiles_.at(player_.getY()).at(player_.getX());
    tiles_.at(player_.getY()).at(player_.getX()) = new Path(' ');
  }

  // Move in the direction, if the landing tile is no Wall
  if(direction == Game::DIRECTION_MOVE_UP)
  {
    cout << "Up" << endl;
    if(tiles_.at(player_.getY()-1).at(player_.getX())->getSymbol() != FIELD_TYPE_WALL)
    {
      player_.setY(player_.getY() - 1);
      steps_--;
      moves_.append(string(1,Game::DIRECTION_FAST_MOVE_UP));
    }
    else
    {
      return -1;
    }
  }
  else if(direction == Game::DIRECTION_MOVE_DOWN)
  {
    cout << "Down" << endl;
    if(tiles_.at(player_.getY()+1).at(player_.getX())->getSymbol() != FIELD_TYPE_WALL)
    {
      player_.setY(player_.getY() + 1);
      steps_--;
      moves_.append(string(1,Game::DIRECTION_FAST_MOVE_DOWN));
    }
    else
    {
      return -1;
    }
  }
  else if(direction == Game::DIRECTION_MOVE_LEFT)
  {
    cout << "Left" << endl;
    if(tiles_.at(player_.getY()).at(player_.getX() - 1)->getSymbol() != FIELD_TYPE_WALL)
    {
      player_.setX(player_.getX() - 1);
      steps_--;
      moves_.append(string(1,Game::DIRECTION_FAST_MOVE_LEFT));
    }
    else
    {
      return -1;
    }
  }
  else if(direction == Game::DIRECTION_MOVE_RIGHT)
  {
    cout << "Right" << endl;
    if(tiles_.at(player_.getY()).at(player_.getX() + 1)->getSymbol() != FIELD_TYPE_WALL)
    {
      player_.setX(player_.getX() + 1);
      steps_--;
      moves_.append(string(1,Game::DIRECTION_FAST_MOVE_RIGHT));
    }
    else
    {
      return -1;
    }
  }

  player_.setTile(getTile(player_.getX(), player_.getY()));

  // Player lands on Teleport tile
  if((player_.getTile()->getSymbol()>=FIELD_TYPE_TELEPORT_MIN) &&
     (player_.getTile()->getSymbol()<=FIELD_TYPE_TELEPORT_MAX))
  {
    if(moveTeleport(player_.getTile()->getSymbol()) == 0)
    {
      return 0;
    }
    else
    {
      return -1;
    }
  }

  // Player lands on Bonus tile
  if((player_.getTile()->getSymbol()>=FIELD_TYPE_BONUS_MIN) &&
    (player_.getTile()->getSymbol()<=FIELD_TYPE_BONUS_MAX))
  {
    steps_ = steps_+((player_.getTile()->getSymbol() - FIELD_TYPE_BONUS_MIN) + 1);
  }

  // Player lands on Quicksand
  if((player_.getTile()->getSymbol() >= FIELD_TYPE_QUICKSAND_MIN) &&
    (player_.getTile()->getSymbol() <= FIELD_TYPE_QUICKSAND_MAX))
  {
    steps_ = steps_- ((player_.getTile()->getSymbol() - FIELD_TYPE_QUICKSAND_MIN) + 1);
  }

  if(player_.getTile()->getSymbol() == FIELD_TYPE_FINISH)
  {
    cout << OUTPUT_MAZE_SOLVED << endl;
    return 1;
  }

  if(steps_ <= 0 )
  {
    steps_ = 0;
    cout << "Game over" << endl;
    return -3;
  }

  // Player lands on Ice
  if((player_.getTile()->getSymbol()) == FIELD_TYPE_ICE)
  {
    movePlayer(direction);
  }

  return 0;
}

//------------------------------------------------------------------------------
int Maze::fastMovePlayer(string directions)
{
  int player_position_x=player_.getX();
  int player_position_y=player_.getY();
  string moves_save=moves_;
  int counter_string=0;
  int return_value=0;

  while(counter_string<directions.size())
  {
    if(directions.at(counter_string)==Game::DIRECTION_FAST_MOVE_UP)
    {
      return_value=movePlayer(Game::DIRECTION_MOVE_UP + Maze::FAST_MOVE_FLAG);
    }
    else if(directions.at(counter_string)==Game::DIRECTION_FAST_MOVE_DOWN)
    {
      return_value=movePlayer(Game::DIRECTION_MOVE_DOWN + Maze::FAST_MOVE_FLAG);
    }
    else if(directions.at(counter_string)==Game::DIRECTION_FAST_MOVE_LEFT)
    {
      return_value=movePlayer(Game::DIRECTION_MOVE_LEFT + Maze::FAST_MOVE_FLAG);
    }
    else if(directions.at(counter_string)==Game::DIRECTION_FAST_MOVE_RIGHT)
    {
      return_value=movePlayer(Game::DIRECTION_MOVE_RIGHT + Maze::FAST_MOVE_FLAG);
    }
    else
    {
      return_value=-1;
    }
    counter_string++;

    if(return_value!=0)
    {
      deleteMaze();
      load(SAVE_FILE_NAME);
      player_.setX(player_position_x);
      player_.setY(player_position_y);
      moves_=moves_save;
      fastMovePlayer(moves_);
      counter_string=directions.size();

      return -1;
    }
  }

  return 0;
}

//------------------------------------------------------------------------------
int Maze::moveTeleport(char symbol)
{
  for (counter_x_ = 0; counter_x_ < tiles_.size(); counter_x_++)
  {
    for (counter_y_ = 0; counter_y_ < tiles_.at(counter_y_).size(); counter_y_++)
    {
      if((tiles_.at(counter_x_).at(counter_y_)->getSymbol() == symbol) &&
        ((counter_x_ != player_.getY()) || (counter_y_ != player_.getX())))
      {
        player_.setY(counter_x_);
        player_.setX(counter_y_);
        player_.setTile(getTile(counter_y_, counter_x_));
        return 0;
      }
    }
  }
  return -1;
}

//------------------------------------------------------------------------------
void Maze::deleteMaze()
{
  for (counter_x_ = 0; counter_x_ < tiles_.size(); counter_x_++)
  {
    for (counter_y_ = 0; counter_y_ < tiles_.at(counter_y_).size(); counter_y_++)
    {
      delete(tiles_.at(counter_x_).at(counter_y_));
    }
  }
}

//------------------------------------------------------------------------------
Tile* Maze::getTile(int x, int y)
{
  //TODO sind da x und y absichtlich vertauscht?
  return tiles_.at(y).at(x);
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
  int filename_counter = 0;
  for(char& filename_letter : filename)
  {
    if(filename_counter == 255)
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


