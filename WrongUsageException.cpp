//------------------------------------------------------------------------------
// WrongUsageException.cpp
//
// Group: Group 10, study assistant: Daniel Ellmeier
//
// Authors: Peter Buerscher (1530750)
// Jakob Guertl (1530763)
//------------------------------------------------------------------------------
//

#include <iostream>
#include "WrongUsageException.h"

using std::cout;
using std::endl;

const string WrongUsageException::WRONG_USAGE_MESSAGE =
  "[ERR] Wrong usage: ./basic [-s <filename1>] [-m <filename2>]";

//------------------------------------------------------------------------------
WrongUsageException::WrongUsageException()
{
  cout << WRONG_USAGE_MESSAGE << endl;
}