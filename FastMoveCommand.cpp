//------------------------------------------------------------------------------
// FastMoveCommand.cpp
//
// Group: Group 10, study assistant: Daniel Ellmeier
//
// Authors: Peter Buerscher (1530750)
// Jakob Guertl (1530763)
//------------------------------------------------------------------------------
//

#include <iostream>
#include "FastMoveCommand.h"

using std::cout;
using std::endl;

//------------------------------------------------------------------------------
FastMoveCommand::FastMoveCommand(string name) : Command(name)
{
  
}

//------------------------------------------------------------------------------
int FastMoveCommand::execute(Game& board, vector<string>& params)
{
  //TODO Get direction from params and validate
  string directions;
  return board.fastMovePlayer(directions);
}