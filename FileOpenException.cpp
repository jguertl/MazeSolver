//------------------------------------------------------------------------------
// FileOpenException.cpp
//
// Group: Group 10, study assistant: Daniel Ellmeier
//
// Authors: Peter Buerscher (1530750)
// Jakob Guertl (1530763)
//------------------------------------------------------------------------------
//

#include <iostream>
#include "FileOpenException.h"

using std::cout;
using std::endl;

const string FileOpenException::FILE_OPEN_MESSAGE =
  "[ERR] File could not be opened.";

//------------------------------------------------------------------------------
FileOpenException::FileOpenException()
{
  cout << FILE_OPEN_MESSAGE << endl;
}