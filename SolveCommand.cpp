//------------------------------------------------------------------------------
// SolveCommand.cpp
//
// Group: Group 10, study assistant: Daniel Ellmeier
//
// Authors: Peter Buerscher (1530750)
// Jakob Guertl (1530763)
//------------------------------------------------------------------------------
//

#include <iostream>
#include "SolveCommand.h"
#include "NoMazeLoadedException.h"
#include "WrongParameterException.h"
#include "Game.h"

using std::cout;
using std::endl;

//------------------------------------------------------------------------------
SolveCommand::SolveCommand(string name) : Command(name)
{
  
}

//------------------------------------------------------------------------------
int SolveCommand::execute(Game& board, vector<string>& params)
{
  if(params.size() == 1)
  {
    checkIfMazeIsLoaded(board);
    return board.solveMaze(false);
  }
  else
  {
    if(params.at(1) == Game::SILENT_COMMAND)
    {
      checkIfMazeIsLoaded(board);
      return board.solveMaze(true);
    }
    else
    {
      throw WrongParameterException();
    }
  }
}

//------------------------------------------------------------------------------
void SolveCommand::checkIfMazeIsLoaded(Game& board)
{
  if(board.isMazeLoaded() == false)
  {
    throw NoMazeLoadedException();
  }
}