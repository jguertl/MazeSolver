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
#include <iostream>
#include "Player.h"
#include "Maze.h"

using std::string;
using std::vector;

//----------------------------------------------------------------------------
// Game Class
// Class to represent a whole game
//
class Game {
  private:
  
    //--------------------------------------------------------------------------
    // Variable which indicates if the game is currently running
    //
    bool running_;
  
    //--------------------------------------------------------------------------
    // Variable which indicates if auto save has been enabled
    //
    bool autoSaveEnabled_;
  
    //--------------------------------------------------------------------------
    // Variable which represents the current player
    //
    Player player_;
  
    //--------------------------------------------------------------------------
    // Variable which represents the current maze
    //
    Maze maze_;
  
    //--------------------------------------------------------------------------
    // Variable which represents the output filename in case of a save
    //
    string outputFilename_;
  
    //--------------------------------------------------------------------------
    // Variable which represents the output filename in case of a save
    //
    string inputFilename_;
  
    //--------------------------------------------------------------------------
    // Variable which is true if a maze has been loaded
    //
    bool is_maze_loaded_;
  
  public:
   
    //--------------------------------------------------------------------------
    // Move Direction "up"
    //
    static const string DIRECTION_MOVE_UP;
  
    //--------------------------------------------------------------------------
    // Move Direction "down"
    //
    static const string DIRECTION_MOVE_DOWN;
  
    //--------------------------------------------------------------------------
    // Move Direction "left"
    //
    static const string DIRECTION_MOVE_LEFT;
  
    //--------------------------------------------------------------------------
    // Move Direction "right"
    //
    static const string DIRECTION_MOVE_RIGHT;
  
    //--------------------------------------------------------------------------
    // Fast Move Direction "u"
    //
    static const char DIRECTION_FAST_MOVE_UP;
  
    //--------------------------------------------------------------------------
    // Fast Move Direction "d"
    //
    static const char DIRECTION_FAST_MOVE_DOWN;
  
    //--------------------------------------------------------------------------
    // Fast Move Direction "l"
    //
    static const char DIRECTION_FAST_MOVE_LEFT;
  
    //--------------------------------------------------------------------------
    // Fast Move Direction "r"
    //
    static const char DIRECTION_FAST_MOVE_RIGHT;
  
    //--------------------------------------------------------------------------
    // Constructor
    //
    Game();

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
    // Start Method
    // Starts the game
    //
    void startGame();

    //--------------------------------------------------------------------------
    // Check Method
    // TODO description
    // @param moves Moves to check
    // @return Returns result of the check operation.
    //
    bool checkMoves(string moves);
 
    //--------------------------------------------------------------------------
    // Show Method
    // Shows the current maze
    // @return TODO
    //
    int showMaze();

    //--------------------------------------------------------------------------
    // Save Method
    // Saves the current maze
    // @param filename Filename of the maze which should be save
    // @return TODO
    //
    int saveMaze(string filename);

    //--------------------------------------------------------------------------
    // Load Method
    // Loads the current maze
    // @param filename Filename of the maze which should be loaded
    // @return TODO
    //
    int loadMaze(string filename);

    //--------------------------------------------------------------------------
    // Move Method
    // Move the player in the given direction
    // @param direction Direction to move
    // @return TODO
    //
    int movePlayer(string direction);
  
    //--------------------------------------------------------------------------
    // Fast Move Method
    // Move the player in the given direction
    // @param directions Directions to move
    // @return TODO
    //
    int fastMovePlayer(string directions);
  
    //--------------------------------------------------------------------------
    // Reset Method
    // Resets the game
    // @return TODO
    //
    int reset();
  
    //--------------------------------------------------------------------------
    // Set output filename method
    // Sets the output filename
    // @param output_filename Path to the output file
    //
    void setOutputFilename(string output_filename);
  
    //--------------------------------------------------------------------------
    // Set input filename method
    // Sets the input filename
    // @param input_filename Path to the input file
    //
    void setInputFilename(string input_filename);
  
    //--------------------------------------------------------------------------
    // Maze loaded method
    // Returns the current loading state of the maze
    // @return the current state 
    //
    bool isMazeLoaded();
};

#endif //GAME_H_INCLUDED

