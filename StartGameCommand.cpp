//------------------------------------------------------------------------------
// StartGameCommand.cpp
//
// Group: Group 10, study assistant: Daniel Ellmeier
//
// Authors: Peter Buerscher (1530750)
// Jakob Guertl (1530763)
//------------------------------------------------------------------------------
//

#include <iostream>
#include "StartGameCommand.h"

using std::cout;
using std::endl;

//------------------------------------------------------------------------------
StartGameCommand::StartGameCommand(string name) : Command(name)
{
  
}

//------------------------------------------------------------------------------
int StartGameCommand::execute(Game& board, vector<string>& params)
{
  board.startGame();
  return 1;
}