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
#include <string>

using std::string;

//----------------------------------------------------------------------------
// Path Class
// Class to represent a path without restrictions
//
class Path : Tile
{
  private:
  
  public:
    
    //--------------------------------------------------------------------------
    // Constructor
    //
    Path();
    
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
    // TODO description
    // @param direction Direction to move
    // @return Returns result of the move operation.
    //
    virtual bool move(string direction) override;
};

#endif //PATH_H_INCLUDED

