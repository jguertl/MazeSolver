//------------------------------------------------------------------------------
// Tile.h
//
// Group: Group 10, study assistant: Daniel Ellmeier
//
// Authors: Peter Buerscher (1530750)
// Jakob Guertl (1530763)
//------------------------------------------------------------------------------
//

#ifndef TILE_H_INCLUDED
#define TILE_H_INCLUDED

#include <string>

using std::string;

//----------------------------------------------------------------------------
// Tile Class
// Class to represent the base class for all tiles inside a maze
//
class Tile
{
  private:

    //--------------------------------------------------------------------------
    // TODO
    //
    char symbol_;

  public:

    //--------------------------------------------------------------------------
    // Constructor
    //
    Tile();

    //--------------------------------------------------------------------------
    // Copy Constructor
    // Makes a copy of another Tile Object.
    // @param orig Original to copy.
    //
    Tile(const Tile& orig);

    //--------------------------------------------------------------------------
    // Destructor
    //
    virtual ~Tile();

    //--------------------------------------------------------------------------
    // Move Method
    // TODO description
    // @param direction Direction to move
    // @return Returns result of the move operation.
    //
    virtual bool move(string direction) = 0;

    //--------------------------------------------------------------------------
    // Setter
    // TODO description
    // @param
    // @return Returns
    //
    void setSymbol(char symbol);

    //--------------------------------------------------------------------------
    // Getter
    // TODO description
    // @param
    // @return Returns
    //
    char getSymbol();
};

#endif //TILE_H_INCLUDED

