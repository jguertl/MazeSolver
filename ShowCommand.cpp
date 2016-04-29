//------------------------------------------------------------------------------
// ShowCommand.cpp
//
// Group: Group 10, study assistant: Daniel Ellmeier
//
// Authors: Peter Buerscher (1530750)
// Jakob Guertl (1530763)
//------------------------------------------------------------------------------
//

#include <iostream>
#include "ShowCommand.h"
#include "NoMazeLoadedException.h"
#include "WrongParameterException.h"
#include "Game.h"

using std::cout;
using std::endl;

//------------------------------------------------------------------------------
ShowCommand::ShowCommand(string name) : Command(name)
{
    
}

//------------------------------------------------------------------------------
int ShowCommand::execute(Game& board, vector<string>& params)
{
  if(params.size() == 1)
  {
    checkIfMazeIsLoaded(board);
    return board.showMaze();
  }
  else
  {
    if(params.at(1) == Game::MORE_COMMAND)
    {
      checkIfMazeIsLoaded(board);
      return board.showExtendedMaze();
    }
    else
    {
      throw WrongParameterException();
    }
  }
}

//------------------------------------------------------------------------------
void ShowCommand::checkIfMazeIsLoaded(Game& board)
{
  if(board.isMazeLoaded() == false)
  {
    throw NoMazeLoadedException();
  }
}