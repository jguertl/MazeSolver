//------------------------------------------------------------------------------
// Bonus.h
//
// Group: Group 10, study assistant: Daniel Ellmeier
//
// Authors: Peter Buerscher (1530750)
// Jakob Guertl (1530763)
//------------------------------------------------------------------------------
//

#ifndef BONUS_H_INCLUDED
#define BONUS_H_INCLUDED

#include "Tile.h"

//------------------------------------------------------------------------------
// Bonus Class
// Class to represent a bonus field which increments the remaining steps
//
class Bonus : public Tile
{
  public:

    //--------------------------------------------------------------------------
    // Constructor
    //
    Bonus();

    //--------------------------------------------------------------------------
    // Constructor
    //
    Bonus(char symbol);

    //--------------------------------------------------------------------------
    // Copy Constructor
    // Makes a copy of another Bonus Object.
    // @param orig Original to copy.
    //
    Bonus(const Bonus& orig);

    //--------------------------------------------------------------------------
    // Destructor
    //
    virtual ~Bonus();

    //--------------------------------------------------------------------------
    // Move Method
    // Checks if a position move on this field is possible
    // @param direction Direction to move
    // @return Returns result of the move operation.
    //
    virtual bool move(string direction) override;
};

#endif //BONUS_H_INCLUDED

