//------------------------------------------------------------------------------
// Counter.cpp
//
// Group: Group 10, study assistant: Daniel Ellmeier
//
// Authors: Peter Buerscher (1530750)
// Jakob Guertl (1530763)
//------------------------------------------------------------------------------
//
#include <iostream>

#include "Counter.h"

//------------------------------------------------------------------------------
Counter::Counter()
{
}

//------------------------------------------------------------------------------
Counter::Counter(char symbol, int id, int value) :
  Tile(symbol, id, value)
{
}

//------------------------------------------------------------------------------
Counter::Counter(const Counter& orig)
{
}

//------------------------------------------------------------------------------
Counter::~Counter()
{
}

//------------------------------------------------------------------------------
bool Counter::move(string direction)
{
  if(getSymbol() == '#')
  {
    return false;
  }
  else
  {
    return true;
  }
  return true;
}
