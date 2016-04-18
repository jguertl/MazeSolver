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

const string OutOfMemoryException::OUT_OF_MEMORY_MESSAGE = "[ERR] Out of memory.";

//------------------------------------------------------------------------------
OutOfMemoryException::OutOfMemoryException()
{
  cout << OUT_OF_MEMORY_MESSAGE << endl;
}