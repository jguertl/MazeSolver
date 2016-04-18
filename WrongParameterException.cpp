//------------------------------------------------------------------------------
// WrongParameterException.cpp
//
// Group: Group 10, study assistant: Daniel Ellmeier
//
// Authors: Peter Buerscher (1530750)
// Jakob Guertl (1530763)
//------------------------------------------------------------------------------
//

#include <iostream>
#include "WrongParameterException.h"

using std::cout;
using std::endl;

const string WrongParameterException::WrongParameterMessage =
  "[ERR] Wrong parameter.";

//------------------------------------------------------------------------------
WrongParameterException::WrongParameterException()
{
  cout << WrongParameterMessage << endl;
}