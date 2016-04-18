//------------------------------------------------------------------------------
// OutOfMemoryException.cpp
//
// Group: Group 10, study assistant: Daniel Ellmeier
//
// Authors: Peter Buerscher (1530750)
// Jakob Guertl (1530763)
//------------------------------------------------------------------------------
//

#include <iostream>
#include "OutOfMemoryException.h"

using std::cout;
using std::endl;

//------------------------------------------------------------------------------
OutOfMemoryException::OutOfMemoryException()
{
  //TODO replace with static constant string
  cout << "[ERR] Out of memory." << endl;
}