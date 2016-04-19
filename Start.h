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
#include <iostream>
#include "Tile.h"

using std::string;
using std::cout;
using std::cin;
using std::endl;

//----------------------------------------------------------------------------
// Start Class
// Class to represent the start field which is the entry point for the game
//
class Start : public Tile
{
  private:

  public:

    //--------------------------------------------------------------------------
    // Constructor
    //
    Start();

    //--------------------------------------------------------------------------
    // Constructor
    //
    Start(char symbol);

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

