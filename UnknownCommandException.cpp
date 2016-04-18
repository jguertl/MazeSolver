//------------------------------------------------------------------------------
// UnknownCommandException.cpp
//
// Group: Group 10, study assistant: Daniel Ellmeier
//
// Authors: Peter Buerscher (1530750)
// Jakob Guertl (1530763)
//------------------------------------------------------------------------------
//

#include <iostream>
#include "UnknownCommandException.h"

using std::cout;
using std::endl;

const string UnknownCommandException::UNKNOWN_COMMAND_MESSAGE =
"[ERR] Unknown command.";

//------------------------------------------------------------------------------
UnknownCommandException::UnknownCommandException()
{
  cout << UNKNOWN_COMMAND_MESSAGE << endl;
}