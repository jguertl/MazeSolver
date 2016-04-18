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

//------------------------------------------------------------------------------
WrongUsageException::WrongUsageException()
{
  cout << "[ERR] Wrong usage: ./basic [-s <filename1>] [-m <filename2>]" << endl;
}