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
#include "InvalidMoveException.h"

using std::cout;
using std::endl;

//------------------------------------------------------------------------------
FastMoveCommand::FastMoveCommand(string name) : Command(name)
{
  
}

//------------------------------------------------------------------------------
int FastMoveCommand::execute(Game& board, vector<string>& params)
{
  string directions = params.at(1);
  for(char& single_direction : directions)
  {
    if(single_direction != board.DIRECTION_FAST_MOVE_LEFT
      && single_direction != board.DIRECTION_FAST_MOVE_RIGHT
      && single_direction != board.DIRECTION_FAST_MOVE_UP
      && single_direction != board.DIRECTION_FAST_MOVE_DOWN)
    {
      throw InvalidMoveException();
    }
  }
  return board.fastMovePlayer(directions);
}