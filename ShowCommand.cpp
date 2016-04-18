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

using std::cout;
using std::endl;

//------------------------------------------------------------------------------
ShowCommand::ShowCommand(string name) : Command(name)
{
    
}

//------------------------------------------------------------------------------
int ShowCommand::execute(Game &board, vector<string> &params)
{
  cout << "ShowCommand execute" << endl;
  return 1;
}