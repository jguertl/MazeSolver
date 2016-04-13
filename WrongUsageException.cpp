//------------------------------------------------------------------------------
// WrongUsageException.cpp
//
// Group: Group 10, study assistant: Daniel Ellmeier
//
// Authors: Armin Adam (1430748)
// Peter Buerscher (1530750)
// Jakob Guertl (1530763)
//------------------------------------------------------------------------------
//

#include "WrongUsageException.h"
#include <iostream>

using std::cout;
using std::endl;

//------------------------------------------------------------------------------
WrongUsageException::WrongUsageException()
{
    cout << "[ERR] Wrong usage: ./basic [-s <filename1>] [-m <filename2>]" << endl;
}