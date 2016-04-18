//------------------------------------------------------------------------------
// Maze.cpp
//
// Group: Group 10, study assistant: Daniel Ellmeier
//
// Authors: Peter Buerscher (1530750)
// Jakob Guertl (1530763)
//------------------------------------------------------------------------------
//

#include "Maze.h"
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

using std::ofstream;
using std::ifstream;
using std::string;
using std::cout;
using std::endl;

//------------------------------------------------------------------------------
Maze::Maze() : steps_(0), moves_(""), counter_(0)
{
    //cout << "Constructor 1" << endl;
}

//------------------------------------------------------------------------------
Maze::~Maze()
{
}

//------------------------------------------------------------------------------
void Maze::loadMaze(const string& path)
{
  cout << "Load from " << path << endl;
  ifstream file ("maze.txt");
  string line;
  char buffer;
  vector<Tile*> buffer_vector;
  std::stringstream sstream;
  Tile* tile_pointer;
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
      if(buffer=='#')
      {
        // Wall
        tile_pointer = new Wall(buffer);
      }else if(buffer==' ')
      {
        // Path
        tile_pointer = new Path(buffer);
      }else if(buffer=='+')
      {
        // Ice
        tile_pointer = new Ice(buffer);
      }else if(buffer=='o')
      {
        // Start
        tile_pointer = new Start(buffer);
      }else if(buffer=='x')
      {
        // Finish
        tile_pointer = new Finish(buffer);
      }else if(buffer>='a' && buffer<='e')
      {
        // Bonus
        tile_pointer = new Bonus(buffer);
      }else if(buffer>='f' && buffer<='j')
      {
        // Quicksand
        tile_pointer = new Quicksand(buffer);
      }else if(buffer>='A' && buffer<='Z')
      {
        // Teleport
        tile_pointer = new Teleport(buffer);
      }else if(buffer=='<' ||
               buffer=='>' ||
               buffer=='^' ||
               buffer=='v')
      {
        // OneWay
        tile_pointer = new OneWay(buffer);
      }

      buffer_vector.push_back(tile_pointer);

      if(buffer=='\n')
      {
        buffer_vector.pop_back();
        tiles_.push_back(buffer_vector);
        buffer_vector.clear();
      }
    }

    file.close();
  }
  else
  {
    cout << "Unable to open file" ;
  }

}

//------------------------------------------------------------------------------
void Maze::saveMaze(const string& path)
{
  cout << "Save to " << path << endl;
  ofstream outfile;

  outfile.open(path.c_str());
  outfile << moves_ << std::endl;
  outfile << steps_ << std::endl;

  for (int i = 0; i < tiles_.size(); i++)
  {
    for (int j = 0; j < tiles_[i].size(); j++)
    {
      outfile << tiles_[i][j]->getSymbol();
    }
    outfile << std::endl;
  }


  outfile.close();
}

//------------------------------------------------------------------------------
void Maze::showMaze()
{
  for (int i = 0; i < tiles_.size(); i++)
  {
    for (int j = 0; j < tiles_[i].size(); j++)
    {
      cout << tiles_[i][j]->getSymbol();
    }
    cout << std::endl;
  }
}

//------------------------------------------------------------------------------
void Maze::showMore()
{
  cout << "Remaining Steps: " << steps_ << std::endl;
  cout << "Moved Steps: " << moves_ << std::endl;
  showMaze();
}

//------------------------------------------------------------------------------
void Maze::deleteMaze()
{
  for (int i = 0; i < tiles_.size(); i++)
  {
    for (int j = 0; j < tiles_[i].size(); j++)
    {
      delete(tiles_[i][j]);
    }
  }
}
