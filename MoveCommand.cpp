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
#include "InvalidMoveException.h"

using std::cout;
using std::endl;

//------------------------------------------------------------------------------
MoveCommand::MoveCommand(string name) : Command(name)
{

}

//------------------------------------------------------------------------------
int MoveCommand::execute(Game& board, vector<string>& params)
{
  string direction = params.at(1);
  if((direction == Game::DIRECTION_MOVE_UP) || (direction == Game::DIRECTION_MOVE_DOWN) ||
     (direction == Game::DIRECTION_MOVE_LEFT) || (direction == Game::DIRECTION_MOVE_RIGHT))
  {
    return board.movePlayer(direction);
  }
  else
  {
    throw InvalidMoveException();
  }
}
