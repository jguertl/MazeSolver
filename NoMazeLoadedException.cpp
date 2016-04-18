//------------------------------------------------------------------------------
// NoMazeLoadedException.cpp
//
// Group: Group 10, study assistant: Daniel Ellmeier
//
// Authors: Peter Buerscher (1530750)
// Jakob Guertl (1530763)
//------------------------------------------------------------------------------
//

#include <iostream>
#include "NoMazeLoadedException.h"

using std::cout;
using std::endl;

const string NoMazeLoadedException::NoMazeLoadedMessage =
  "[ERR] No maze loaded";

//------------------------------------------------------------------------------
NoMazeLoadedException::NoMazeLoadedException()
{
  cout << NoMazeLoadedMessage << endl;
}