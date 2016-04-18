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

#include <string>
#include "Tile.h"

using std::string;

//----------------------------------------------------------------------------
// Quicksand Class
// Class to represent a quicksand field which decrements the remaining steps
//
class Quicksand : Tile
{
  private:
    
  public:
    
    //--------------------------------------------------------------------------
    // Constructor
    //
    Quicksand();
    
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
    // TODO description
    // @param direction Direction to move
    // @return Returns result of the move operation.
    //
    virtual bool move(string direction) override;
};

#endif //QUICKSAND_H_INCLUDED

