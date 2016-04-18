//------------------------------------------------------------------------------
// SaveCommand.cpp
//
// Group: Group 10, study assistant: Daniel Ellmeier
//
// Authors: Peter Buerscher (1530750)
// Jakob Guertl (1530763)
//------------------------------------------------------------------------------
//

#include <iostream>
#include "SaveCommand.h"

using std::cout;
using std::endl;

//------------------------------------------------------------------------------
SaveCommand::SaveCommand(string name) : Command(name)
{

}

//------------------------------------------------------------------------------
int SaveCommand::execute(Game &board, vector<string> &params)
{
  cout << "SaveCommand execute" << endl;
  return 1;
}