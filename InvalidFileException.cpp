//------------------------------------------------------------------------------
// InvalidFileException.cpp
//
// Group: Group 10, study assistant: Daniel Ellmeier
//
// Authors: Peter Buerscher (1530750)
// Jakob Guertl (1530763)
//------------------------------------------------------------------------------
//

#include <iostream>
#include "InvalidFileException.h"

using std::cout;
using std::endl;

const string InvalidFileException::INVALID_FILE_EXCEPTION =
"[ERR] Invalid file.";

//------------------------------------------------------------------------------
InvalidFileException::InvalidFileException()
{
  cout << INVALID_FILE_EXCEPTION << endl;
}