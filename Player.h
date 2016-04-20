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

#include <iostream>
#include <string>
#include "Tile.h"

using std::string;
using std::cout;
using std::cin;
using std::endl;

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
    Tile* tile_;

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
    // Move Method
    // TODO description
    // @param direction Direction to move
    // @return Returns result of the move operation.
    //
    void move(string direction);

    //--------------------------------------------------------------------------
    // Fastmove Method
    // TODO description
    // @param moves Directions
    // @return Returns result of the move operation.
    //
    void fastMove(string moves);

    //--------------------------------------------------------------------------
    // Setter tile_
    // TODO description
    // @param tile
    //
    void setTile(Tile* tile);

    //--------------------------------------------------------------------------
    // Getter tile_
    // TODO description
    // @return tile
    //
    Tile* getTile();

    //--------------------------------------------------------------------------
    // Setter x_
    // TODO description
    // @param x new x value
    //
    void setX(int x);

    //--------------------------------------------------------------------------
    // Getter x_
    // TODO description
    // @return x x-value
    //
    int getX();

    //--------------------------------------------------------------------------
    // Setter y_
    // TODO description
    // @param y new y value
    //
    void setY(int y);

    //--------------------------------------------------------------------------
    // Getter y_
    // TODO description
    // @return y y-value
    //
    int getY();
};

#endif //PLAYER_H_INCLUDED

