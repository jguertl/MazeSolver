//------------------------------------------------------------------------------
// NoMoreStepsException.cpp
//
// Group: Group 10, study assistant: Daniel Ellmeier
//
// Authors: Peter Buerscher (1530750)
// Jakob Guertl (1530763)
//------------------------------------------------------------------------------
//

#include <iostream>
#include "NoMoreStepsException.h"

using std::cout;
using std::endl;

const string NoMoreStepsException::NoMoreStepsMessage =
  "[ERR] No more steps possible.";

//------------------------------------------------------------------------------
NoMoreStepsException::NoMoreStepsException()
{
  cout << NoMoreStepsMessage << endl;
}