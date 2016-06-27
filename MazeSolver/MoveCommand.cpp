//------------------------------------------------------------------------------
// MoveCommand.cpp
//
// Group: Group 10, study assistant: Daniel Ellmeier
//
// Authors: Peter Buerscher (1530750)
// Jakob Guertl (1530763)
//------------------------------------------------------------------------------
//

#include "MoveCommand.h"
#include "WrongParameterException.h"
#include "NoMazeLoadedException.h"

//------------------------------------------------------------------------------
MoveCommand::MoveCommand(string name) : Command(name)
{
  
}

//------------------------------------------------------------------------------
int MoveCommand::execute(Game& board, vector<string>& params)
{
  string direction = params.at(1);
  if((direction == Game::DIRECTION_MOVE_UP) ||
    (direction == Game::DIRECTION_MOVE_DOWN) ||
    (direction == Game::DIRECTION_MOVE_LEFT) ||
    (direction == Game::DIRECTION_MOVE_RIGHT))
  {
    if(board.isMazeLoaded() == false)
    {
      throw NoMazeLoadedException();
    }
    
    return board.movePlayer(direction);
  }
  else
  {
    throw WrongParameterException();
  }

}
