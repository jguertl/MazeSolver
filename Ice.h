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
    Ice(char symbol);

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
    // TODO description
    // @param direction Direction to move
    // @return Returns result of the move operation.
    //
    virtual bool move(string direction) override;
};

#endif //ICE_H_INCLUDED

