//------------------------------------------------------------------------------
// Start.h
//
// Group: Group 10, study assistant: Daniel Ellmeier
//
// Authors: Peter Buerscher (1530750)
// Jakob Guertl (1530763)
//------------------------------------------------------------------------------
//

#ifndef START_H_INCLUDED
#define START_H_INCLUDED

#include "Tile.h"

//------------------------------------------------------------------------------
// Start Class
// Class to represent the start field which is the entry point for the game
//
class Start : public Tile
{
  public:

    //--------------------------------------------------------------------------
    // Constructor
    //
    Start();

    //--------------------------------------------------------------------------
    // Constructor
    //
    Start(char symbol, int id, int value);

    //--------------------------------------------------------------------------
    // Copy Constructor
    // Makes a copy of another Start Object.
    // @param orig Original to copy.
    //
    Start(const Start& orig);

    //--------------------------------------------------------------------------
    // Destructor
    //
    virtual ~Start();

    //--------------------------------------------------------------------------
    // Move Method
    // Checks if a position move on this field is possible
    // @param direction Direction to move
    // @return bool Returns result of the move operation.
    //
    virtual bool move(string direction) override;
};

#endif //START_H_INCLUDED

