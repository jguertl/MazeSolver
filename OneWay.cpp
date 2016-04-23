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
  if((getSymbol() == Game::ONE_WAY_RIGHT) &&
    (direction == Game::DIRECTION_MOVE_RIGHT))
  {
    return true;
  }
  else if((getSymbol() == Game::ONE_WAY_LEFT) &&
    (direction == Game::DIRECTION_MOVE_LEFT))
  {
    return true;
  }
  else if((getSymbol() == Game::ONE_WAY_UP) &&
    (direction == Game::DIRECTION_MOVE_UP))
  {
    return true;
  }
  else if((getSymbol() == Game::ONE_WAY_DOWN) &&
    (direction == Game::DIRECTION_MOVE_DOWN))
  {
    return true;
  }
  else
  {
    return false;
  }
}
