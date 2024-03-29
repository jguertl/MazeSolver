//------------------------------------------------------------------------------
// Ice.h
//
// Group: Group 10, study assistant: Daniel Ellmeier
//
// Authors: Peter Buerscher (1530750)
// Jakob Guertl (1530763)
//------------------------------------------------------------------------------
//

#ifndef ICE_H_INCLUDED
#define ICE_H_INCLUDED

#include "Tile.h"

//------------------------------------------------------------------------------
// Ice Class
// Class to represent an ice field
//
class Ice : public Tile
{
  public:

    //--------------------------------------------------------------------------
    // Constructor
    //
    Ice();

    //--------------------------------------------------------------------------
    // Constructor
    //
    Ice(char symbol, int id, int value);

    //--------------------------------------------------------------------------
    // Copy Constructor
    // Makes a copy of another Ice Object.
    // @param orig Original to copy.
    //
    Ice(const Ice& orig);

    //--------------------------------------------------------------------------
    // Destructor
    //
    virtual ~Ice();

    //--------------------------------------------------------------------------
    // Move Method
    // Checks if a position move on this field is possible
    // @param direction Direction to move
    // @return bool Returns result of the move operation.
    //
    virtual bool move(string direction) override;
};

#endif //ICE_H_INCLUDED

