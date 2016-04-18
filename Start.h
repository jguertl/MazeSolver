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

#include <string>
#include "Tile.h"

using std::string;

//----------------------------------------------------------------------------
// Start Class
// Class to represent the start field which is the entry point for the game
//
class Start : Tile
{
  private:
  
  public:
  
    //--------------------------------------------------------------------------
    // Constructor
    //
    Start();
  
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
    // TODO description
    // @param direction Direction to move
    // @return Returns result of the move operation.
    //
    virtual bool move(string direction) override;
};

#endif //START_H_INCLUDED

