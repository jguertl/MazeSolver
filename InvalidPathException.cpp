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

const string InvalidPathException::InvalidPathMessage =
"[ERR] Invalid path.";

//------------------------------------------------------------------------------
InvalidPathException::InvalidPathException()
{
  cout << InvalidPathMessage << endl;
}