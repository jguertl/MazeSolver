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

const string InvalidMoveException::INVALID_MOVE_EXCEPTION =
  "[ERR] Invalid move.";

//------------------------------------------------------------------------------
InvalidMoveException::InvalidMoveException()
{
  cout << INVALID_MOVE_EXCEPTION << endl;
}