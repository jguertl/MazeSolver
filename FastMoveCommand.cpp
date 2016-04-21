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
#include "WrongParameterException.h"
#include "NoMazeLoadedException.h"

using std::cout;
using std::endl;

//------------------------------------------------------------------------------
FastMoveCommand::FastMoveCommand(string name) : Command(name)
{
  
}

//------------------------------------------------------------------------------
int FastMoveCommand::execute(Game& board, vector<string>& params)
{
  if(board.isMazeLoaded() == false)
  {
    throw NoMazeLoadedException();
  }

  string directions = params.at(1);
  for(char& single_direction : directions)
  {
    if(single_direction != Game::DIRECTION_FAST_MOVE_LEFT
      && single_direction != Game::DIRECTION_FAST_MOVE_RIGHT
      && single_direction != Game::DIRECTION_FAST_MOVE_UP
      && single_direction != Game::DIRECTION_FAST_MOVE_DOWN)
    {
      throw WrongParameterException();
    }
  }
  return board.fastMovePlayer(directions);
}