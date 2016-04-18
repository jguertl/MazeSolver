//------------------------------------------------------------------------------
// InvalidMoveException.cpp
//
// Group: Group 10, study assistant: Daniel Ellmeier
//
// Authors: Peter Buerscher (1530750)
// Jakob Guertl (1530763)
//------------------------------------------------------------------------------
//

#include <iostream>
#include "InvalidMoveException.h"

using std::cout;
using std::endl;

const string InvalidMoveException::InvalidMoveMessage =
"[ERR] Invalid move.";

//------------------------------------------------------------------------------
InvalidMoveException::InvalidMoveException()
{
  cout << InvalidMoveMessage << endl;
}