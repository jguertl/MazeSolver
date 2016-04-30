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

const string NoMazeLoadedException::NO_MAZE_LOADED_MESSAGE =
  "[ERR] No maze loaded.";

//------------------------------------------------------------------------------
NoMazeLoadedException::NoMazeLoadedException()
{
  cout << NO_MAZE_LOADED_MESSAGE << endl;
}