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
  if((getSymbol()=='<') && (direction.compare("left")==0))
  {
    return true;
  }
  else if((getSymbol()=='>') && (direction.compare("right")==0))
  {
    return true;
  }
  else if((getSymbol()=='^') && (direction.compare("up")==0))
  {
    return true;
  }
  else if((getSymbol()=='v') && (direction.compare("down")==0))
  {
    return true;
  }
  else
  {
    return false;
  }
}
