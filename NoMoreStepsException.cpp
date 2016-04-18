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

const string NoMoreStepsException::NO_MORE_STEPS_MESSAGE =
  "[ERR] No more steps possible.";

//------------------------------------------------------------------------------
NoMoreStepsException::NoMoreStepsException()
{
  cout << NO_MORE_STEPS_MESSAGE << endl;
}