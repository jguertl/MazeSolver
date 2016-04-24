//------------------------------------------------------------------------------
// Quicksand.h
//
// Group: Group 10, study assistant: Daniel Ellmeier
//
// Authors: Peter Buerscher (1530750)
// Jakob Guertl (1530763)
//------------------------------------------------------------------------------
//

#ifndef QUICKSAND_H_INCLUDED
#define QUICKSAND_H_INCLUDED

#include "Tile.h"

//------------------------------------------------------------------------------
// Quicksand Class
// Class to represent a quicksand field which decrements the remaining steps
//
class Quicksand : public Tile
{
  public:

    //--------------------------------------------------------------------------
    // Constructor
    //
    Quicksand();

    //--------------------------------------------------------------------------
    // Constructor
    //
    Quicksand(char symbol);

    //--------------------------------------------------------------------------
    // Copy Constructor
    // Makes a copy of another Quicksand Object.
    // @param orig Original to copy.
    //
    Quicksand(const Quicksand& orig);

    //--------------------------------------------------------------------------
    // Destructor
    //
    virtual ~Quicksand();

    //--------------------------------------------------------------------------
    // Move Method
    // Checks if a position move on this field is possible
    // @param direction Direction to move
    // @return bool Returns result of the move operation.
    //
    virtual bool move(string direction) override;
};

#endif //QUICKSAND_H_INCLUDED

