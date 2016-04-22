//------------------------------------------------------------------------------
// Wall.h
//
// Group: Group 10, study assistant: Daniel Ellmeier
//
// Authors: Peter Buerscher (1530750)
// Jakob Guertl (1530763)
//------------------------------------------------------------------------------
//

#ifndef WALL_H_INCLUDED
#define WALL_H_INCLUDED

#include "Tile.h"

//------------------------------------------------------------------------------
// Wall Class
// Class to represent a wall field which cannot be entered
//
class Wall : public Tile
{
  public:

    //--------------------------------------------------------------------------
    // Constructor
    //
    Wall();

    //--------------------------------------------------------------------------
    // Constructor
    //
    Wall(char symbol);

    //--------------------------------------------------------------------------
    // Copy Constructor
    // Makes a copy of another Wall Object.
    // @param orig Original to copy.
    //
    Wall(const Wall& orig);

    //--------------------------------------------------------------------------
    // Destructor
    //
    virtual ~Wall();

    //--------------------------------------------------------------------------
    // Move Method
    // TODO description
    // @param direction Direction to move
    // @return Returns result of the move operation.
    //
    virtual bool move(string direction) override;
};

#endif //WALL_H_INCLUDED

