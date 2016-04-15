//------------------------------------------------------------------------------
// OutOfMemoryException.cpp
//
// Group: Group 10, study assistant: Daniel Ellmeier
//
// Authors: Peter Buerscher (1530750)
// Jakob Guertl (1530763)
//------------------------------------------------------------------------------
//

#include "OutOfMemoryException.h"
#include <iostream>

using std::cout;
using std::endl;

//------------------------------------------------------------------------------
OutOfMemoryException::OutOfMemoryException()
{
    cout << "[ERR] Out of memory." << endl;
}