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
#include <memory>

using std::string;
using std::unique_ptr;

//----------------------------------------------------------------------------
// Tile Class
// Class to represent the base class for all tiles inside a maze
//
class Tile
{
  private:

    //--------------------------------------------------------------------------
    // The symbol which refers to this tile
    //
    char symbol_;

    //--------------------------------------------------------------------------
    // Unique identification number
    //
    int id_;

    //--------------------------------------------------------------------------
    // The value of the tile
    //
    int value_;

  public:

    //--------------------------------------------------------------------------
    // Constructor
    //
    Tile();

    //--------------------------------------------------------------------------
    // Constructor for three arguments
    //
    Tile(char symbol, int id, int value);

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
    // Checks if a position move on this field is possible
    // @param direction Direction to move
    // @return bool Returns result of the move operation.
    //
    virtual bool move(string direction) = 0;

    //--------------------------------------------------------------------------
    // Setter Method
    // Sets the current symbol
    // @param symbol The given symbol as a char
    //
    void setSymbol(char symbol);

    //--------------------------------------------------------------------------
    // Getter Method
    // Gets the current symbol
    // @return char Returns the symbol as a char
    //
    char getSymbol();

    //--------------------------------------------------------------------------
    // Setter Method
    // Sets the current value
    // @param symbol The given value
    //
    void setValue(char symbol);

    //--------------------------------------------------------------------------
    // Getter Method
    // Gets the current value
    // @return int returns the value
    //
    int getValue();

    //--------------------------------------------------------------------------
    // Setter Method
    // Sets the current id
    // @param id The given id
    //
    void setId(int id);

    //--------------------------------------------------------------------------
    // Getter Method
    // Gets the current id
    // @return int returns the id
    //
    int getId();
};

#endif //TILE_H_INCLUDED

