//------------------------------------------------------------------------------
// Counter.h
//
// Group: Group 10, study assistant: Daniel Ellmeier
//
// Authors: Peter Buerscher (1530750)
// Jakob Guertl (1530763)
//------------------------------------------------------------------------------
//

#ifndef COUNTER_H_INCLUDED
#define COUNTER_H_INCLUDED

#include "Tile.h"

//------------------------------------------------------------------------------
// Counter Class
// Class to represent a Counter field which decrements with every move on it
// counterpart field
//
class Counter : public Tile
{
public:
  
  //--------------------------------------------------------------------------
  // Constructor
  //
  Counter();
  
  //--------------------------------------------------------------------------
  // Constructor
  //
  Counter(char symbol);
  
  //--------------------------------------------------------------------------
  // Copy Constructor
  // Makes a copy of another Counter Object.
  // @param orig Original to copy.
  //
  Counter(const Counter& orig);
  
  //--------------------------------------------------------------------------
  // Destructor
  //
  virtual ~Counter();
  
  //--------------------------------------------------------------------------
  // Move Method
  // Checks if a position move on this field is possible
  // @param direction Direction to move
  // @return bool Returns result of the move operation.
  //
  virtual bool move(string direction) override;
  
};

#endif //COUNTER_H_INCLUDED

