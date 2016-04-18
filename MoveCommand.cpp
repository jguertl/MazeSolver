//------------------------------------------------------------------------------
// MoveCommand.cpp
//
// Group: Group 10, study assistant: Daniel Ellmeier
//
// Authors: Peter Buerscher (1530750)
// Jakob Guertl (1530763)
//------------------------------------------------------------------------------
//

#include <iostream>
#include "MoveCommand.h"

using std::cout;
using std::endl;

//------------------------------------------------------------------------------
MoveCommand::MoveCommand(string name) : Command(name)
{

}

//------------------------------------------------------------------------------
int MoveCommand::execute(Game& board, vector<string>& params)
{
  //TODO Get direction from params and validate
  string direction;
  return board.movePlayer(direction);
}