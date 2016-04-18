//------------------------------------------------------------------------------
// Game.h
//
// Group: Group 10, study assistant: Daniel Ellmeier
//
// Authors: Peter Buerscher (1530750)
// Jakob Guertl (1530763)
//------------------------------------------------------------------------------
//

#ifndef GAME_H_INCLUDED
#define GAME_H_INCLUDED

#include <string>
#include "Maze.h"
#include "Player.h"

using std::string;

//----------------------------------------------------------------------------
// Game Class
// Class to represent a whole game
//
class Game {
  private:
    
  public:
    
    //--------------------------------------------------------------------------
    // Constructor
    //
    Game();
    
    //--------------------------------------------------------------------------
    // Constructor
    // @param loadfile Path to load
    // @param savefile Path to save
    //
    Game(string loadfile, string savefile);
    
    //--------------------------------------------------------------------------
    // Copy Constructor
    // Makes a copy of another Game Object.
    // @param orig Original to copy.
    //
    Game(const Game& orig);
    
    //--------------------------------------------------------------------------
    // Destructor
    //
    virtual ~Game();
    
    //--------------------------------------------------------------------------
    // TODO wirklich Public?
    //
    Maze maze_;
    
    //--------------------------------------------------------------------------
    // TODO wirklich Public?
    //
    Player player_;
    
    //--------------------------------------------------------------------------
    // Start Method
    // Starts the game
    //
    void startGame();
};

#endif //GAME_H_INCLUDED

