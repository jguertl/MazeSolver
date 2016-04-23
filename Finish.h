//------------------------------------------------------------------------------
// Finish.h
//
// Group: Group 10, study assistant: Daniel Ellmeier
//
// Authors: Peter Buerscher (1530750)
// Jakob Guertl (1530763)
//------------------------------------------------------------------------------
//

#ifndef FINISH_H_INCLUDED
#define FINISH_H_INCLUDED

#include "Tile.h"

//------------------------------------------------------------------------------
// Finish Class
// Class to represent the finish field
//
class Finish : public Tile
{
  public:

    //--------------------------------------------------------------------------
    // Constructor
    //
    Finish();

    //--------------------------------------------------------------------------
    // Constructor
    //
    Finish(char symbol);

    //--------------------------------------------------------------------------
    // Copy Constructor
    // Makes a copy of another Finish Object.
    // @param orig Original to copy.
    //
    Finish(const Finish& orig);

    //--------------------------------------------------------------------------
    // Destructor
    //
    virtual ~Finish();

    //--------------------------------------------------------------------------
    // Move Method
    // Checks if a position move on this field is possible
    // @param direction Direction to move
    // @return Returns result of the move operation.
    //
    virtual bool move(string direction) override;
};

#endif //FINISH_H_INCLUDED

