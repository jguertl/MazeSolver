//------------------------------------------------------------------------------
// ShowMoreCommand.cpp
//
// Group: Group 10, study assistant: Daniel Ellmeier
//
// Authors: Peter Buerscher (1530750)
// Jakob Guertl (1530763)
//------------------------------------------------------------------------------
//

#include <iostream>
#include "ShowMoreCommand.h"
#include "NoMazeLoadedException.h"

using std::cout;
using std::endl;

//------------------------------------------------------------------------------
ShowMoreCommand::ShowMoreCommand(string name) : Command(name)
{

}

//------------------------------------------------------------------------------
int ShowMoreCommand::execute(Game& board, vector<string>& params)
{
  if(board.isMazeLoaded() == false)
    throw NoMazeLoadedException();

  return board.showExtendedMaze();
}