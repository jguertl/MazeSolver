//------------------------------------------------------------------------------
// Hole.h
//
// Group: Group 10, study assistant: Daniel Ellmeier
//
// Authors: Peter Buerscher (1530750)
// Jakob Guertl (1530763)
//------------------------------------------------------------------------------
//

#ifndef HOLE_H_INCLUDED
#define HOLE_H_INCLUDED

#include "Tile.h"

//------------------------------------------------------------------------------
// Hole Class
// Class to represent a hole field which transfers to the start
// counterpart field
//
class Hole : public Tile
{
public:
  
  //--------------------------------------------------------------------------
  // Constructor
  //
  Hole();
  
  //--------------------------------------------------------------------------
  // Constructor
  //
  Hole(char symbol);
  
  //--------------------------------------------------------------------------
  // Copy Constructor
  // Makes a copy of another Hole Object.
  // @param orig Original to copy.
  //
  Hole(const Hole& orig);
  
  //--------------------------------------------------------------------------
  // Destructor
  //
  virtual ~Hole();
  
  //--------------------------------------------------------------------------
  // Move Method
  // Checks if a position move on this field is possible
  // @param direction Direction to move
  // @return bool Returns result of the move operation.
  //
  virtual bool move(string direction) override;
  
};

#endif //HOLE_H_INCLUDED

