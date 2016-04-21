//------------------------------------------------------------------------------
// SaveCommand.cpp
//
// Group: Group 10, study assistant: Daniel Ellmeier
//
// Authors: Peter Buerscher (1530750)
// Jakob Guertl (1530763)
//------------------------------------------------------------------------------
//

#include <iostream>
#include "SaveCommand.h"
#include "WrongParameterException.h"
#include "NoMazeLoadedException.h"

using std::cout;
using std::endl;

//------------------------------------------------------------------------------
SaveCommand::SaveCommand(string name) : Command(name)
{

}

//------------------------------------------------------------------------------
int SaveCommand::execute(Game& board, vector<string>& params)
{
  string filename = params.at(1);
  if(Maze::isFilenameValid(filename) == false)
  {
    throw WrongParameterException();
  }

  if(board.isMazeLoaded() == false)
  {
    throw NoMazeLoadedException();
  }

  return board.saveMaze(filename);
}