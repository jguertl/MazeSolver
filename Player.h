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

#include "Tile.h"

//------------------------------------------------------------------------------
// Player Class
// Class to represent a player inside the maze
//
class Player
{
  private:

    //--------------------------------------------------------------------------
    // X coordinate
    //
    int x_;

    //--------------------------------------------------------------------------
    // Y coordinate
    //
    int y_;

    //--------------------------------------------------------------------------
    // Current tile
    //
    char tile_;

  public:

    //--------------------------------------------------------------------------
    // Constructor
    //
    Player();

    //--------------------------------------------------------------------------
    // Constructor
    //
    Player(int position_x, int position_y);

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
    // Setter tile_
    // Sets the current tile
    // @param tile Tile to set
    //
    void setTile(char tile);

    //--------------------------------------------------------------------------
    // Getter tile_
    // returns the current tile
    // @return Tile* Tile to return
    //
    char getTile();

    //--------------------------------------------------------------------------
    // Setter x_
    // Sets the x value
    // @param x new x value
    //
    void setX(int x);

    //--------------------------------------------------------------------------
    // Getter x_
    // Returns the x value
    // @return int x-value
    //
    int getX();

    //--------------------------------------------------------------------------
    // Setter y_
    // Sets the y value
    // @param y new y value
    //
    void setY(int y);

    //--------------------------------------------------------------------------
    // Getter y_
    // Returns the y value
    // @return int y-value
    //
    int getY();
};

#endif //PLAYER_H_INCLUDED

