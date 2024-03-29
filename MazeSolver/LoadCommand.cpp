//------------------------------------------------------------------------------
// LoadCommand.cpp
//
// Group: Group 10, study assistant: Daniel Ellmeier
//
// Authors: Peter Buerscher (1530750)
// Jakob Guertl (1530763)
//------------------------------------------------------------------------------
//

#include <iostream>
#include "LoadCommand.h"
#include "Maze.h"
#include "WrongParameterException.h"

using std::cout;
using std::endl;

//------------------------------------------------------------------------------
LoadCommand::LoadCommand(string name) : Command(name)
{
    
}

//------------------------------------------------------------------------------
int LoadCommand::execute(Game &board, vector<string> &params)
{
  string filename = params.at(1);
  if(Maze::isFilenameValid(filename) == false)
  {
    throw WrongParameterException();
  }

  return board.loadMaze(filename);
}