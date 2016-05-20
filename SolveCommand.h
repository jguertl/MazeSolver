//------------------------------------------------------------------------------
// SolveCommand.h
//
// Group: Group 10, study assistant: Daniel Ellmeier
//
// Authors: Peter Buerscher (1530750)
// Jakob Guertl (1530763)
//------------------------------------------------------------------------------
//

#ifndef SOLVECOMMAND_H_INCLUDED
#define SOLVECOMMAND_H_INCLUDED

#include <string>
#include <vector>
#include "Command.h"
#include "Game.h"

using std::string;
using std::vector;

//----------------------------------------------------------------------------
// Solve Command Class
// Class which executes a solve instruction
//
class SolveCommand : Command
{
private:
  
  //--------------------------------------------------------------------------
  // Checks if the current maze is loaded
  // @param board The board which should be checked
  void checkIfMazeIsLoaded(Game& board);
  
public:
  
  //--------------------------------------------------------------------------
  // Constructor
  SolveCommand(string name);
  
  //--------------------------------------------------------------------------
  // Executes the command.
  // @param board The board where action should be performed on
  // @param params Possible parameters needed for the execution
  // @return Integer representing the success of the action
  int execute(Game& board, vector<string>& params);
};

#endif //SOLVECOMMAND_H_INCLUDED