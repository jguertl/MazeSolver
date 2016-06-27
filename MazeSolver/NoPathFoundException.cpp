//------------------------------------------------------------------------------
// NoPathFoundException.cpp
//
// Group: Group 10, study assistant: Daniel Ellmeier
//
// Authors: Peter Buerscher (1530750)
// Jakob Guertl (1530763)
//------------------------------------------------------------------------------
//

#include <iostream>
#include "NoPathFoundException.h"

using std::cout;
using std::endl;

const string NoPathFoundException::NO_PATH_FOUND_EXCEPTION =
"[ERR] No path found.";

//------------------------------------------------------------------------------
NoPathFoundException::NoPathFoundException()
{
  cout << NO_PATH_FOUND_EXCEPTION << endl;
}