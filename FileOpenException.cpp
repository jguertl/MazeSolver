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

const string FileOpenException::FileOpenMessage =
"[ERR] File could not be opened.";

//------------------------------------------------------------------------------
FileOpenException::FileOpenException()
{
  cout << FileOpenMessage << endl;
}