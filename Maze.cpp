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

using std::ofstream;
using std::ifstream;
using std::string;
using std::cout;
using std::endl;

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

//------------------------------------------------------------------------------
Maze::Maze() : steps_(0), moves_("")
{
    //cout << "Constructor 1" << endl;
}

//------------------------------------------------------------------------------
Maze::~Maze()
{
}

//------------------------------------------------------------------------------
void Maze::load(const string& path)
{
  cout << "Load from " << path << endl;
  ifstream file ("maze.txt");
  string line;
  char buffer;
  vector<Tile*> buffer_vector;
  std::stringstream sstream;
  counter_x_ = 0;
  counter_y_ = 0;
  if (file.is_open())
  {
    std::getline(file, moves_);
    std::getline(file, line);
    sstream<<line;
    sstream>>steps_;
    sstream.str("");
    sstream.clear();

    while(file.get(buffer))
    {
      if(buffer == FIELD_TYPE_WALL)
      {
        // Wall
        buffer_vector.push_back(new Wall(buffer));
      }
      else if(buffer==' ')
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
      }
      else if(buffer==FIELD_TYPE_ONEWAY_LEFT ||
              buffer==FIELD_TYPE_ONEWAY_RIGHT ||
              buffer==FIELD_TYPE_ONEWAY_UP ||
              buffer==FIELD_TYPE_ONEWAY_DOWN)
      {
        // OneWay
        buffer_vector.push_back(new OneWay(buffer));
      }

      counter_x_++;
      if(buffer=='\n')
      {
        tiles_.push_back(buffer_vector);
        buffer_vector.clear();
        counter_y_++;
        counter_x_=0;
      }
    }
    player_.setTile(tiles_[player_.getY()][player_.getX()]);
    file.close();
  }
  else
  {
    cout << "Unable to open file";
  }

}

//------------------------------------------------------------------------------
void Maze::save(const string& path)
{
  cout << "Save to " << path << endl;
  ofstream outfile;

  outfile.open(path.c_str());
  outfile << moves_ << endl;
  outfile << steps_ << endl;

  for (counter_x_ = 0; counter_x_ < tiles_.size(); counter_y_++)
  {
    for (counter_y_ = 0; counter_y_ < tiles_[counter_x_].size(); counter_y_++)
    {
      outfile << tiles_[counter_x_][counter_y_]->getSymbol();
    }
    outfile << endl;
  }

  outfile.close();
}

//------------------------------------------------------------------------------
void Maze::show()
{
  for (counter_x_ = 0; counter_y_ < tiles_.size(); counter_x_++)
  {
    for (counter_y_ = 0; counter_y_ < tiles_[counter_x_].size(); counter_y_++)
    {
      if((counter_x_ == player_.getY()) && (counter_y_ == player_.getX()))
      {
        cout << FIELD_TYPE_PLAYER;
      }
      else
      {
        cout << tiles_[counter_x_][counter_y_]->getSymbol();
      }
    }
    cout << endl;
  }
}

//------------------------------------------------------------------------------
void Maze::showMore()
{
  cout << "Remaining Steps: " << steps_ << endl;
  cout << "Moved Steps: " << moves_ << endl;
  show();
}

//------------------------------------------------------------------------------
int Maze::movePlayer(string direction)
{
  // check if move is in a valid direction
  if(player_.getTile()->move(direction)==false)
  {
    cout << "[ERR] Invalid move." << endl;
    return -1;
  }

  if(player_.getTile()->getSymbol()=='x')
  {
    cout << "Game is over." << endl;
    return -1;
  }

  // delete Bonus Tile
  if((player_.getTile()->getSymbol()>='a') &&
     (player_.getTile()->getSymbol()<='e'))
  {
    delete tiles_[player_.getY()][player_.getX()];
    tiles_[player_.getY()][player_.getX()] = new Path(' ');
  }

  // Move in the direction, if the landing tile is no Wall
  if(direction == DIRECTION_MOVE_UP)
  {
    cout << "Up" << endl;
    if(tiles_[player_.getY()-1][player_.getX()]->getSymbol()!=FIELD_TYPE_WALL)
    {
      player_.setY(player_.getY()-1);
      steps_--;
      moves_.append("u");
    }
    else
    {
      return -1;
    }
  }
  else if(direction.compare("down")==0)
  {
    cout << "Down" << endl;
    if(tiles_[player_.getY()+1][player_.getX()]->getSymbol()!=FIELD_TYPE_WALL)
    {
      player_.setY(player_.getY()+1);
      steps_--;
      moves_.append("d");
    }
    else
    {
      return -1;
    }
  }
  else if(direction.compare("left")==0)
  {
    cout << "Left" << endl;
    if(tiles_[player_.getY()][player_.getX()-1]->getSymbol()!=FIELD_TYPE_WALL)
    {
      player_.setX(player_.getX()-1);
      steps_--;
      moves_.append("l");
    }
    else
    {
      return -1;
    }
  }
  else if(direction.compare("right")==0)
  {
    cout << "Right" << endl;
    if(tiles_[player_.getY()][player_.getX()+1]->getSymbol()!=FIELD_TYPE_WALL)
    {
      player_.setX(player_.getX()+1);
      steps_--;
      moves_.append("r");
    }
    else
    {
      return -1;
    }
  }

  player_.setTile(getTile(player_.getX(), player_.getY()));
  //cout << "New Tile Position: " << player_.getTile()->getSymbol() << endl;

  // Player lands on Teleport tile
  if((player_.getTile()->getSymbol()>=FIELD_TYPE_TELEPORT_MIN) &&
     (player_.getTile()->getSymbol()<=FIELD_TYPE_TELEPORT_MAX))
  {
    if(moveTeleport(player_.getTile()->getSymbol())==0)
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
    steps_=steps_+((player_.getTile()->getSymbol() - FIELD_TYPE_BONUS_MIN) + 1);
  }

  // Player lands on Quicksand
  if((player_.getTile()->getSymbol()>=FIELD_TYPE_QUICKSAND_MIN) &&
     (player_.getTile()->getSymbol()<=FIELD_TYPE_QUICKSAND_MAX))
  {
    steps_=steps_-((player_.getTile()->getSymbol() - FIELD_TYPE_QUICKSAND_MIN) + 1);
  }

  if(player_.getTile()->getSymbol()==FIELD_TYPE_FINISH)
  {
    cout << "Congratulation! You solved the maze." << endl;
    return 1;
  }

  if(steps_<=0)
  {
    steps_=0;
    cout << "Game over" << endl;
    return -2;
  }
  // Player lands on Ice
  if(player_.getTile()->getSymbol()== FIELD_TYPE_ICE)
  {
    movePlayer(direction);
  }

  return 0;
}

//------------------------------------------------------------------------------
int Maze::moveTeleport(char symbol)
{
  cout << "Move Teleport: >" << symbol << "<" << endl;
  cout << "Before Position X:" << player_.getX() << " Y: " << player_.getY() << endl;
  for (int i = 0; i < tiles_.size(); i++)
  {
    for (int j = 0; j < tiles_[i].size(); j++)
    {
      if((tiles_[i][j]->getSymbol()==symbol) &&
         ((i!=player_.getY()) ||
         (j!=player_.getX())))
      {

        cout << "Found second " << symbol << " at X:" << j << " Y: " << i << endl;
        player_.setY(i);
        player_.setX(j);
        player_.setTile(getTile(j, i));
        cout << "Afterwards Position X:" << player_.getX() << " Y: " << player_.getY() << endl;
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
    for (counter_y_ = 0; counter_y_ < tiles_[counter_y_].size(); counter_y_++)
    {
      delete(tiles_[counter_x_][counter_y_]);
    }
  }
}

//------------------------------------------------------------------------------
Tile* Maze::getTile(int x, int y)
{
  //TODO sind da x und y absichtlich vertauscht?
  return tiles_[y][x];
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


