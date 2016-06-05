//------------------------------------------------------------------------------
// Path.h
//
// Group: Group 10, study assistant: Daniel Ellmeier
//
// Authors: Peter Buerscher (1530750)
// Jakob Guertl (1530763)
//------------------------------------------------------------------------------
//

#ifndef PATH_H_INCLUDED
#define PATH_H_INCLUDED

#include "Tile.h"

//----------------------------------------------------------------------------
// Path Class
// Class to represent a path without restrictions
//
class Path : public Tile
{
  public:

    //--------------------------------------------------------------------------
    // Constructor
    //
    Path();

    //--------------------------------------------------------------------------
    // Constructor
    //
    Path(char symbol, int id, int value);

    //--------------------------------------------------------------------------
    // Copy Constructor
    // Makes a copy of another Path Object.
    // @param orig Original to copy.
    //
    Path(const Path& orig);

    //--------------------------------------------------------------------------
    // Destructor
    //
    virtual ~Path();

    //--------------------------------------------------------------------------
    // Move Method
    // Checks if a position move on this field is possible
    // @param direction Direction to move
    // @return bool Returns result of the move operation.
    //
    virtual bool move(string direction) override;
};

#endif //PATH_H_INCLUDED

