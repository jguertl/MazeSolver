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

const string FileAccessException::FILE_ACCESS_EXCEPTION =
  "[ERR] File could not be written.";

//------------------------------------------------------------------------------
FileAccessException::FileAccessException()
{
  cout << FILE_ACCESS_EXCEPTION << endl;
}