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

const string OutOfMemoryException::OutOfMemoryMessage = "[ERR] Out of memory.";

//------------------------------------------------------------------------------
OutOfMemoryException::OutOfMemoryException()
{
  cout << OutOfMemoryMessage << endl;
}