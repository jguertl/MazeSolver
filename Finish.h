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

#include <string>
#include "Tile.h"

using std::string;

//----------------------------------------------------------------------------
// Finish Class
// Class to represent the finish field
//
class Finish : public Tile
{
  private:

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
    // TODO description
    // @param direction Direction to move
    // @return Returns result of the move operation.
    //
    bool move(string direction);
};

#endif //FINISH_H_INCLUDED

