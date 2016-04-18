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
  vector<char> buffer_vector;
  std::stringstream sstream;
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
      //std::cout << "Read " << buffer << std::endl;
      buffer_vector.push_back(buffer);

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

  /*
  cout << "Moves: " << moves_ << endl;
  cout << "Steps: " << steps_ << endl;
  cout << "Size of Maze: " << tiles_.size() << endl;
  cout << "Size of Line: " << tiles_[0].size() << endl;

  for (int i = 0; i < tiles_.size(); i++)
  {
    for (int j = 0; j < tiles_[i].size(); j++)
    {
      cout << tiles_[i][j];
    }
    cout << std::endl;
  }
  */

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
      outfile << tiles_[i][j];
    }
    outfile << std::endl;
  }

  outfile.close();
}

