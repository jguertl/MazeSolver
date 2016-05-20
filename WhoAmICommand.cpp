//------------------------------------------------------------------------------
// WhoAmICommand.cpp
//
// Group: Group 10, study assistant: Daniel Ellmeier
//
// Authors: Peter Buerscher (1530750)
// Jakob Guertl (1530763)
//------------------------------------------------------------------------------
//

#include "WhoAmICommand.h"

//------------------------------------------------------------------------------
WhoAmICommand::WhoAmICommand(string name) : Command(name)
{
  
}

//------------------------------------------------------------------------------
int WhoAmICommand::execute(Game& board, vector<string>& params)
{
  return board.whoami();
}