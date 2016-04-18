//------------------------------------------------------------------------------
// FileAccessException.cpp
//
// Group: Group 10, study assistant: Daniel Ellmeier
//
// Authors: Peter Buerscher (1530750)
// Jakob Guertl (1530763)
//------------------------------------------------------------------------------
//

#include <iostream>
#include "FileAccessException.h"

using std::cout;
using std::endl;

const string FileAccessException::FileAccessMessage =
"[ERR] File could not be written.";

//------------------------------------------------------------------------------
FileAccessException::FileAccessException()
{
  cout << FileAccessMessage << endl;
}