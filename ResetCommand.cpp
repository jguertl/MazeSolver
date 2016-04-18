//------------------------------------------------------------------------------
// ResetCommand.cpp
//
// Group: Group 10, study assistant: Daniel Ellmeier
//
// Authors: Peter Buerscher (1530750)
// Jakob Guertl (1530763)
//------------------------------------------------------------------------------
//

#include <iostream>
#include "ResetCommand.h"

using std::cout;
using std::endl;

//------------------------------------------------------------------------------
ResetCommand::ResetCommand(string name) : Command(name)
{
  
}

//------------------------------------------------------------------------------
int ResetCommand::execute(Game& board, vector<string>& params)
{
  return board.reset();
}