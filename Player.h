//------------------------------------------------------------------------------
// Player.h
//
// Group: Group 10, study assistant: Daniel Ellmeier
//
// Authors: Peter Buerscher (1530750)
// Jakob Guertl (1530763)
//------------------------------------------------------------------------------
//
#ifndef PLAYER_H_INCLUDED
#define PLAYER_H_INCLUDED

#include <string>
#include "Tile.h"

using std::string;

//----------------------------------------------------------------------------
// Player Class
// Class to represent a player inside the maze
//
class Player
{
private:
  
  //--------------------------------------------------------------------------
  // TODO
  //
  int x_;
  
  //--------------------------------------------------------------------------
  // TODO
  //
  int y_;
 
  //--------------------------------------------------------------------------
  // TODO
  //
  Tile tile_;
    
public:
    
  //--------------------------------------------------------------------------
  // Constructor
  //
  Player();
    
  //--------------------------------------------------------------------------
  // Copy Constructor
  // Makes a copy of another Player Object.
  // @param orig Original to copy.
  //
  Player(const Player& orig);
    
  //--------------------------------------------------------------------------
  // Destructor
  //
  virtual ~Player();

  //--------------------------------------------------------------------------
  // Move Method
  // TODO description
  // @param direction Direction to move
  // @return Returns result of the move operation.
  //
  void move(string direction);
  
  //--------------------------------------------------------------------------
  // Check Method
  // TODO description
  // @param moves Moves to check
  // @return Returns result of the check operation.
  //
  bool checkMoves(string moves);
};

#endif //PLAYER_H_INCLUDED

