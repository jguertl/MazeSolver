//------------------------------------------------------------------------------
// WhoAmICommand.h
//
// Group: Group 10, study assistant: Daniel Ellmeier
//
// Authors: Peter Buerscher (1530750)
// Jakob Guertl (1530763)
//------------------------------------------------------------------------------
//

#ifndef WHOAMICOMMAND_H_INCLUDED
#define WHOAMICOMMAND_H_INCLUDED

#include <string>
#include <vector>
#include "Command.h"
#include "Game.h"

using std::string;
using std::vector;

//----------------------------------------------------------------------------
// Who Am I Command Class
// Class which executes a whoami instruction
//
class WhoAmICommand : Command
{
public:
  
  //--------------------------------------------------------------------------
  // Constructor
  WhoAmICommand(string name);
  
  //--------------------------------------------------------------------------
  // Executes the command.
  // @param board The board where action should be performed on
  // @param params Possible parameters needed for the execution
  // @return Integer representing the success of the action
  int execute(Game& board, vector<string>& params);
};

#endif //WHOAMICOMMAND_H_INCLUDED