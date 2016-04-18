//------------------------------------------------------------------------------
// InvalidPathException.cpp
//
// Group: Group 10, study assistant: Daniel Ellmeier
//
// Authors: Peter Buerscher (1530750)
// Jakob Guertl (1530763)
//------------------------------------------------------------------------------
//

#include <iostream>
#include "InvalidPathException.h"

using std::cout;
using std::endl;

const string InvalidPathException::INVALID_PATH_EXCEPTION =
"[ERR] Invalid path.";

//------------------------------------------------------------------------------
InvalidPathException::InvalidPathException()
{
  cout << INVALID_PATH_EXCEPTION << endl;
}