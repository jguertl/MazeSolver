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
#include "Game.h"
#include "Maze.h"
#include "FileOpenException.h"
#include "FileAccessException.h"
#include "InvalidFileException.h"
#include "InvalidPathException.h"
#include "NoMoreStepsException.h"
#include "InvalidMoveException.h"

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
const char Maze::FILENAME_DEFINITION_LOWERCASE_MIN = 'a';
const char Maze::FILENAME_DEFINITION_LOWERCASE_MAX = 'z';
const char Maze::FILENAME_DEFINITION_UPPERCASE_MIN = 'A';
const char Maze::FILENAME_DEFINITION_UPPERCASE_MAX = 'Z';
const char Maze::FILENAME_DEFINITION_NUMBER_MIN = '0';
const char Maze::FILENAME_DEFINITION_NUMBER_MAX = '9';
const char Maze::FILENAME_DEFINITION_DOT = '.';
const char Maze::FILENAME_DEFINITION_SLASH = '/';
const int Maze::BONUS_OFFSET = 1;
const int Maze::QUICKSAND_OFFSET = 1;
const int Maze::GAME_WON = 1;
const int Maze::SUCCESS = 0;
const int Maze::ERROR = -1;
const int Maze::OUT_OF_STEPS = -2;
const int Maze::INVALID_MOVE = -3;

//------------------------------------------------------------------------------
Maze::Maze() : steps_(0)
{
}

//------------------------------------------------------------------------------
Maze::~Maze()
{
  // TODO PETER
  // - vor und nach einem operator ein Leerzeichen (z.b. sstream << line)
  // - kein Leerzeichen vor einer for-Schleife (z.b. for(int i....) )
  // - Wenn du länger als 80 Zeichen bist, dann auf die nächste Zeile und genau
  //   2 Leerzeilen einrücken
}

//------------------------------------------------------------------------------
int Maze::load(const string& path)
{
  deleteMaze();
  ifstream file (path);
  string line;
  string moves_save;
  char buffer;
  char teleport_duplicate_check;
  int start_check = 0;
  int finish_check = 0;
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

    if((moves_.size() > steps_))
    {
      file.close();
      deleteMaze();
      throw InvalidFileException();
    }

    while(file.get(buffer))
    {
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
        start_check++;
      }
      else if(buffer==FIELD_TYPE_FINISH)
      {
        // Finish
        buffer_vector.push_back(new Finish(buffer));
        finish_check++;
      }
      else if((buffer>=FIELD_TYPE_BONUS_MIN) &&
              (buffer<=FIELD_TYPE_BONUS_MAX))
      {
        // Bonus
        buffer_vector.push_back(new Bonus(buffer));
      }
      else if((buffer>=FIELD_TYPE_QUICKSAND_MIN) &&
              (buffer<=FIELD_TYPE_QUICKSAND_MAX))
      {
        // Quicksand
        buffer_vector.push_back(new Quicksand(buffer));
      }
      else if((buffer>=FIELD_TYPE_TELEPORT_MIN) &&
              (buffer<=FIELD_TYPE_TELEPORT_MAX))
      {
        // Teleport
        buffer_vector.push_back(new Teleport(buffer));
        teleport_symbols.push_back(buffer);
        //cout << "Teleport Unsorted: " << buffer << endl;
      }
      else if((buffer==FIELD_TYPE_ONEWAY_LEFT) ||
              (buffer==FIELD_TYPE_ONEWAY_RIGHT) ||
              (buffer==FIELD_TYPE_ONEWAY_UP) ||
              (buffer==FIELD_TYPE_ONEWAY_DOWN))
      {
        // OneWay
        buffer_vector.push_back(new OneWay(buffer));
      }else if(buffer != '\n')
      {
        //cout << "Input File not valid  A" << endl;
        deleteMaze();
        throw InvalidFileException();
      }

      counter_x_++;
      if(buffer=='\n')
      {
        tiles_.push_back(buffer_vector);

        // Check Maze
        if((size_check >= 0) && (size_check != (int)buffer_vector.size()))
        {
          //cout << "Input File not valid  B" << endl;
          file.close();
          deleteMaze();
          throw InvalidFileException();
        }
        if((buffer_vector.front()->getSymbol() != FIELD_TYPE_WALL) &&
           (buffer_vector.back()->getSymbol() != FIELD_TYPE_WALL))
        {
          //cout << "Input File not valid  C" << endl;
          file.close();
          deleteMaze();
          throw InvalidFileException();
        }

        size_check = buffer_vector.size();
        buffer_vector.clear();
        counter_y_++;
        counter_x_=0;
      }
    }
    // Check if first line only contains Walls
    for(counter_x_=0; counter_x_<tiles_.front().size(); counter_x_++)
    {
      if(tiles_.front().at(counter_x_)->getSymbol() != FIELD_TYPE_WALL)
      {
        //cout << "Input File not valid  D" << endl;
        file.close();
        deleteMaze();
        throw InvalidFileException();
      }
    }
    // Check if last line only contains Walls
    for(counter_x_=0; counter_x_<tiles_.back().size(); counter_x_++)
    {
      if(tiles_.back().at(counter_x_)->getSymbol() != FIELD_TYPE_WALL)
      {
        //cout << "Input File not valid  E" << endl;
        file.close();
        deleteMaze();
        throw InvalidFileException();
      }
    }

    // Check if one start and one finish are in the Maze
    if((start_check!=1) || (finish_check!=1))
    {
      //cout << "Start or Finish Error" << endl;
      file.close();
      deleteMaze();
      throw InvalidFileException();
    }

    // Check all Teleports
    teleport_duplicate_check=0;
    sort(teleport_symbols.begin(), teleport_symbols.end());
    while(teleport_symbols.size()>1)
    {
      //cout << "Teleport Sorted: " << teleport_symbols.back() << endl;
      buffer = teleport_symbols.back();
      if(buffer==teleport_duplicate_check)
      {
        //cout << "Teleport Error More than Two" << endl;
        file.close();
        deleteMaze();
        throw InvalidFileException();
      }
      teleport_duplicate_check=buffer;
      teleport_symbols.pop_back();
      if(buffer != teleport_symbols.back())
      {
        //cout << "Teleport Error Single Symbol" << endl;
        file.close();
        deleteMaze();
        throw InvalidFileException();
      }
      //cout << "Teleport Sorted: " << teleport_symbols.back() << endl;
      teleport_symbols.pop_back();

    }
    if(teleport_symbols.size())
    {
      //cout << "Teleport Error Single Symbol" << endl;
      file.close();
      deleteMaze();
      throw InvalidFileException();
    }

    player_.setTile(tiles_.at(player_.getY()).at(player_.getX()));
    file.close();
    save(SAVE_FILE_NAME);
    moves_save=moves_;
    fastMovePlayer(moves_);
    moves_=moves_save;
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
  }

  outputfile << original_steps_ << endl;

  for (counter_y_ = 0; counter_y_ < tiles_.size(); counter_y_++)
  {
    for (counter_x_ = 0; counter_x_ < tiles_.at(counter_y_).size(); counter_x_++)
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
  //cout << "Show" << endl;
  for (counter_y_ = 0; counter_y_ < tiles_.size(); counter_y_++)
  {
    for (counter_x_ = 0; counter_x_ < tiles_.at(counter_y_).size(); counter_x_++)
    {
      if((counter_y_ == player_.getY()) && (counter_x_ == player_.getX()))
      {
        cout << FIELD_TYPE_PLAYER;
      }
      else
      {
        cout << tiles_.at(counter_y_).at(counter_x_)->getSymbol();
      }
    }
    cout << endl;
  }
  return SUCCESS;
}

//------------------------------------------------------------------------------
int Maze::showMore()
{
  //cout << "Show More" << endl;
  cout << Maze::OUTPUT_REMAINING_STEPS << steps_ << endl;
  cout << Maze::OUTPUT_MOVED_STEPS << moves_ << endl;
  show();
  return SUCCESS;
}

//------------------------------------------------------------------------------
int Maze::movePlayer(string direction)
{
  // check if player is out of steps
  if(steps_ <= 0 )
  {
    steps_ = 0;
    //cout << "Game over" << endl;
    return OUT_OF_STEPS;
  }

  if(direction.back()!=FAST_MOVE_FLAG)
  {
    if(player_.getTile()->getSymbol()==FIELD_TYPE_FINISH)
    {
      cout << "[ERR] No more steps possible." << endl;
      return GAME_WON;
    }
  }
  else
  {
    direction.pop_back();
  }

  if(direction.back()==ICE_MOVE_FLAG)
  {
    direction.pop_back();
  }
  else
  {
    steps_--;
  }

  // check if move is in a valid direction
  if(player_.getTile()->move(direction) == false)
  {
    cout << "[ERR] Invalid move." << endl;
    return INVALID_MOVE;
  }

  // delete Bonus Tile
  if((player_.getTile()->getSymbol()>=FIELD_TYPE_BONUS_MIN) &&
     (player_.getTile()->getSymbol()<=FIELD_TYPE_BONUS_MAX))
  {
    delete tiles_.at(player_.getY()).at(player_.getX());
    tiles_.at(player_.getY()).at(player_.getX()) = new Path(' ');
  }

  // Move in the direction, if the landing tile is no Wall
  if(direction == Game::DIRECTION_MOVE_UP)
  {
    //cout << "Up" << endl;
    if(tiles_.at(player_.getY()-1).at(player_.getX())->getSymbol() != FIELD_TYPE_WALL)
    {
      if(tiles_.at(player_.getY()).at(player_.getX())->getSymbol() != FIELD_TYPE_ICE)
      {
        moves_+=Game::DIRECTION_FAST_MOVE_UP;
      }
      player_.setY(player_.getY() - 1);
    }
    else
    {
      return INVALID_MOVE;
    }
  }
  else if(direction == Game::DIRECTION_MOVE_DOWN)
  {
    //cout << "Down" << endl;
    if(tiles_.at(player_.getY()+1).at(player_.getX())->getSymbol() != FIELD_TYPE_WALL)
    {
      if(tiles_.at(player_.getY()).at(player_.getX())->getSymbol() != FIELD_TYPE_ICE)
      {
        moves_+=Game::DIRECTION_FAST_MOVE_DOWN;
      }
      player_.setY(player_.getY() + 1);
    }
    else
    {
      return INVALID_MOVE;
    }
  }
  else if(direction == Game::DIRECTION_MOVE_LEFT)
  {
    //cout << "Left" << endl;
    if(tiles_.at(player_.getY()).at(player_.getX() - 1)->getSymbol() != FIELD_TYPE_WALL)
    {
      if(tiles_.at(player_.getY()).at(player_.getX())->getSymbol() != FIELD_TYPE_ICE)
      {
        moves_+=Game::DIRECTION_FAST_MOVE_LEFT;
      }
      player_.setX(player_.getX() - 1);
    }
    else
    {
      return INVALID_MOVE;
    }
  }
  else if(direction == Game::DIRECTION_MOVE_RIGHT)
  {
    //cout << "Right" << endl;
    if(tiles_.at(player_.getY()).at(player_.getX() + 1)->getSymbol() != FIELD_TYPE_WALL)
    {
      if(tiles_.at(player_.getY()).at(player_.getX())->getSymbol() != FIELD_TYPE_ICE)
      {
        moves_+=Game::DIRECTION_FAST_MOVE_RIGHT;
      }
      player_.setX(player_.getX() + 1);
    }
    else
    {
      return INVALID_MOVE;
    }
  }

  player_.setTile(getTile(player_.getX(), player_.getY()));

  // Player lands on Teleport tile
  if((player_.getTile()->getSymbol()>=FIELD_TYPE_TELEPORT_MIN) &&
     (player_.getTile()->getSymbol()<=FIELD_TYPE_TELEPORT_MAX))
  {
    if(moveTeleport(player_.getTile()->getSymbol()) == SUCCESS)
    {
      return SUCCESS;
    }
    else
    {
      return INVALID_MOVE;
    }
  }
  // Player lands on Bonus tile
  if((player_.getTile()->getSymbol()>=FIELD_TYPE_BONUS_MIN) &&
    (player_.getTile()->getSymbol()<=FIELD_TYPE_BONUS_MAX))
  {
    steps_ = steps_+((player_.getTile()->getSymbol() - FIELD_TYPE_BONUS_MIN) + BONUS_OFFSET);
  }

  // Player lands on Quicksand
  if((player_.getTile()->getSymbol() >= FIELD_TYPE_QUICKSAND_MIN) &&
    (player_.getTile()->getSymbol() <= FIELD_TYPE_QUICKSAND_MAX))
  {
    steps_ = steps_- ((player_.getTile()->getSymbol() - FIELD_TYPE_QUICKSAND_MIN) + QUICKSAND_OFFSET);
  }

  if(steps_ <= 0 )
  {
    steps_ = 0;
    //cout << "Game over" << endl;
    return OUT_OF_STEPS;
  }

  // Player lands on Ice
  if((player_.getTile()->getSymbol()) == FIELD_TYPE_ICE)
  {
    // Slide in the direction, if the landing tile is no Wall
    if((direction == Game::DIRECTION_MOVE_UP) &&
            (tiles_.at(player_.getY()-1).at(player_.getX())->getSymbol() != FIELD_TYPE_WALL))
    {
      movePlayer(direction+ICE_MOVE_FLAG);
    }
    else if((direction == Game::DIRECTION_MOVE_DOWN) &&
            (tiles_.at(player_.getY() + 1).at(player_.getX())->getSymbol() != FIELD_TYPE_WALL))
    {
      movePlayer(direction+ICE_MOVE_FLAG);
    }
    else if((direction == Game::DIRECTION_MOVE_LEFT) &&
            (tiles_.at(player_.getY()).at(player_.getX() - 1)->getSymbol() != FIELD_TYPE_WALL))
    {
      movePlayer(direction+ICE_MOVE_FLAG);
    }
    else if((direction == Game::DIRECTION_MOVE_RIGHT) &&
            (tiles_.at(player_.getY()).at(player_.getX() + 1)->getSymbol() != FIELD_TYPE_WALL))
    {
      movePlayer(direction+ICE_MOVE_FLAG);
    }
  }
  return SUCCESS;
}

//------------------------------------------------------------------------------
int Maze::fastMovePlayer(string directions)
{
  int player_position_x=player_.getX();
  int player_position_y=player_.getY();
  string moves_save=moves_;
  unsigned int counter_string=0;
  int return_value=0;

  if(player_.getTile()->getSymbol()==FIELD_TYPE_FINISH)
  {
    cout << "[ERR] No more steps possible." << endl;
    return GAME_WON;
  }
  while(counter_string<directions.size())
  {
    //cout << "Fast: " << directions.at(counter_string) << endl;
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
      return_value=INVALID_MOVE;
    }
    counter_string++;

    if((return_value!=SUCCESS) &&
       (return_value!=GAME_WON))
    {
      deleteMaze();
      load(SAVE_FILE_NAME);
      player_.setX(player_position_x);
      player_.setY(player_position_y);
      moves_save=moves_;
      fastMovePlayer(moves_);
      moves_=moves_save;
      if(return_value==OUT_OF_STEPS)
      {
        throw NoMoreStepsException();
      }
      else if(return_value==INVALID_MOVE)
      {
        throw InvalidMoveException();
      }
    }
  }
  if(player_.getTile()->getSymbol()==FIELD_TYPE_FINISH)
  {
    cout << OUTPUT_MAZE_SOLVED << endl;
    return GAME_WON;
  }
  return return_value;
}

//------------------------------------------------------------------------------
int Maze::moveTeleport(char symbol)
{
  for (counter_y_ = 0; counter_y_ < tiles_.size(); counter_y_++)
  {
    for(counter_x_ = 0; counter_x_ < tiles_.at(counter_y_).size(); counter_x_++)
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
  for(counter_y_ = tiles_.size()-1; counter_y_ >= 0; counter_y_--)
  {
    for(counter_x_ = tiles_.at(counter_y_).size()-1; counter_x_ >= 0; counter_x_--)
    {
      delete(tiles_.at(counter_y_).at(counter_x_));
    }
    tiles_.at(counter_y_).clear();
  }
  tiles_.clear();
  return SUCCESS;
}

//------------------------------------------------------------------------------
Tile* Maze::getTile(int x, int y)
{
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


