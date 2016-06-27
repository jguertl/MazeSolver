//------------------------------------------------------------------------------
// AlreadySolvedException.cpp
//
// Group: Group 10, study assistant: Daniel Ellmeier
//
// Authors: Peter Buerscher (1530750)
// Jakob Guertl (1530763)
//------------------------------------------------------------------------------
//

#include <iostream>
#include "AlreadySolvedException.h"

using std::cout;
using std::endl;

const string AlreadySolvedException::ALREADY_SOLVED_EXCEPTION =
"[ERR] You already solved the maze.";

//------------------------------------------------------------------------------
AlreadySolvedException::AlreadySolvedException()
{
  cout << ALREADY_SOLVED_EXCEPTION << endl;
}