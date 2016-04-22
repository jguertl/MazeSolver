//------------------------------------------------------------------------------
// Teleport.h
//
// Group: Group 10, study assistant: Daniel Ellmeier
//
// Authors: Peter Buerscher (1530750)
// Jakob Guertl (1530763)
//------------------------------------------------------------------------------
//

#ifndef TELEPORT_H_INCLUDED
#define TELEPORT_H_INCLUDED

#include "Tile.h"

//------------------------------------------------------------------------------
// Teleport Class
// Class to represent a teleport field which transfers to the matchting
// counterpart field
//
class Teleport : public Tile
{
  public:

    //--------------------------------------------------------------------------
    // Constructor
    //
    Teleport();

    //--------------------------------------------------------------------------
    // Constructor
    //
    Teleport(char symbol);

    //--------------------------------------------------------------------------
    // Copy Constructor
    // Makes a copy of another Teleport Object.
    // @param orig Original to copy.
    //
    Teleport(const Teleport& orig);

    //--------------------------------------------------------------------------
    // Destructor
    //
    virtual ~Teleport();

    //--------------------------------------------------------------------------
    // Move Method
    // TODO description
    // @param direction Direction to move
    // @return Returns result of the move operation.
    //
    virtual bool move(string direction) override;

};

#endif //TELEPORT_H _INCLUDED

