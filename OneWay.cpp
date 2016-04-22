//------------------------------------------------------------------------------
// OneWay.cpp
//
// Group: Group 10, study assistant: Daniel Ellmeier
//
// Authors: Peter Buerscher (1530750)
// Jakob Guertl (1530763)
//------------------------------------------------------------------------------
//

#include "OneWay.h"


//------------------------------------------------------------------------------
OneWay::OneWay()
{
}

//------------------------------------------------------------------------------
OneWay::OneWay(char symbol)
{
  setSymbol(symbol);
}



//------------------------------------------------------------------------------
OneWay::OneWay(const OneWay& orig)
{
}


//------------------------------------------------------------------------------
OneWay::~OneWay()
{
}

//------------------------------------------------------------------------------
bool OneWay::move(string direction)
{
  if((getSymbol() == Game::DIRECTION_FAST_MOVE_RIGHT) &&
    (direction == Game::DIRECTION_MOVE_RIGHT))
  {
    return true;
  }
  else if((getSymbol() == Game::DIRECTION_FAST_MOVE_LEFT) &&
    (direction == Game::DIRECTION_MOVE_LEFT))
  {
    return true;
  }
  else if((getSymbol() == Game::DIRECTION_FAST_MOVE_UP) &&
    (direction == Game::DIRECTION_MOVE_UP))
  {
    return true;
  }
  else if((getSymbol() == Game::DIRECTION_FAST_MOVE_DOWN) &&
    (direction == Game::DIRECTION_MOVE_DOWN))
  {
    return true;
  }
  else
  {
    return false;
  }
}
