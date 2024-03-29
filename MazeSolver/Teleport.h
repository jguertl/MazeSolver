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
    Teleport(char symbol, int id, int value);

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
    // Checks if a position move on this field is possible
    // @param direction Direction to move
    // @return bool Returns result of the move operation.
    //
    virtual bool move(string direction) override;

};

#endif //TELEPORT_H_INCLUDED

