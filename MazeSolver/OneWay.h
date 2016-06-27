//------------------------------------------------------------------------------
// OneWay.h
//
// Group: Group 10, study assistant: Daniel Ellmeier
//
// Authors: Peter Buerscher (1530750)
// Jakob Guertl (1530763)
//------------------------------------------------------------------------------
//

#ifndef ONEWAY_H_INCLUDED
#define ONEWAY_H_INCLUDED

#include "Game.h"
#include "Tile.h"

//------------------------------------------------------------------------------
// OneWay Class
// Class to represent a field with only one available direction
//
class OneWay : public Tile
{
  public:

    //--------------------------------------------------------------------------
    // Constructor
    //
    OneWay();

    //--------------------------------------------------------------------------
    // Constructor
    //
    OneWay(char symbol, int id, int value);

    //--------------------------------------------------------------------------
    // Copy Constructor
    // Makes a copy of another OneWay Object.
    // @param orig Original to copy.
    //
    OneWay(const OneWay& orig);

    //--------------------------------------------------------------------------
    // Destructor
    //
    virtual ~OneWay();

    //--------------------------------------------------------------------------
    // Move Method
    // Checks if a position move on this field is possible
    // @param direction Direction to move
    // @return bool Returns result of the move operation.
    //
    virtual bool move(string direction) override;
};

#endif //ONEWAY_H_INCLUDED

