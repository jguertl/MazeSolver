//------------------------------------------------------------------------------
// WrongParameterCountException.cpp
//
// Group: Group 10, study assistant: Daniel Ellmeier
//
// Authors: Peter Buerscher (1530750)
// Jakob Guertl (1530763)
//------------------------------------------------------------------------------
//

#include <iostream>
#include "WrongParameterCountException.h"

using std::cout;
using std::endl;

const string WrongParameterCountException::WrongParameterCountMessage =
  "[ERR] Wrong parameter count.";

//------------------------------------------------------------------------------
WrongParameterCountException::WrongParameterCountException()
{
  cout << WrongParameterCountMessage << endl;
}