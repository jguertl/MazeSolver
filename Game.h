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
#include <vector>
#include "Player.h"
#include "Maze.h"

using std::string;
using std::vector;

//------------------------------------------------------------------------------
// Game Class
// Class to represent a whole game
//
class Game
{
  private:

    //--------------------------------------------------------------------------
    // Variable which indicates if the game is currently running
    //
    bool running_;

    //--------------------------------------------------------------------------
    // Variable which indicates if auto save has been enabled
    //
    bool auto_save_enabled_;

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
    string output_filename_;

    //--------------------------------------------------------------------------
    // Variable which is true if a maze has been loaded
    //
    bool is_maze_loaded_;

    //--------------------------------------------------------------------------
    // Variable representing the prompt text
    //
    static const string PROMPT_TEXT;

    //--------------------------------------------------------------------------
    // Variable representing the quit text
    //
    static const string QUIT_TEXT;

    //--------------------------------------------------------------------------
    // Variable representing the quit command
    //
    static const string QUIT_COMMAND;

    //--------------------------------------------------------------------------
    // Variable representing the quit command
    //
    static const string LOAD_COMMAND;

    //--------------------------------------------------------------------------
    // Variable representing the show command
    //
    static const string SHOW_COMMAND;

    //--------------------------------------------------------------------------
    // Variable representing the save command
    //
    static const string SAVE_COMMAND;

    //--------------------------------------------------------------------------
    // Variable representing the reset command
    //
    static const string RESET_COMMAND;

    //--------------------------------------------------------------------------
    // Variable representing the move command
    //
    static const string MOVE_COMMAND;

    //--------------------------------------------------------------------------
    // Variable representing the fastmove command
    //
    static const string FASTMOVE_COMMAND;
  
    //--------------------------------------------------------------------------
    // Output string naming the finished game
    //
    static const string OUTPUT_MAZE_SOLVED;
  
    //--------------------------------------------------------------------------
    // Split String
    // Helper Method to split a string
    // @param input String which should be splitted
    // @param delimiter Char to split with
    // @return return a vector with the splitted string
    //
    vector<string> splitString(string input, char delimiter);
  
    //--------------------------------------------------------------------------
    // No more steps method
    // Gets called when no more steps are available
    //
    void handleNoMoreSteps();

    //--------------------------------------------------------------------------
    // Lowercase method
    // Returns the current command transformed to lowercase
    // @param command the given command
    // @return the lowercase command
    //
    string toLowercase(string command);

    //--------------------------------------------------------------------------
    // Quit command method
    // Quit Command has been entered
    // @param splitted_command the command splitted by whitespace
    //
    void quitCommandSelected(vector<string> splitted_command);

    //--------------------------------------------------------------------------
    // Load command method
    // Load Command has been entered
    // @param splitted_command the command splitted by whitespace
    //
    void loadCommandSelected(vector<string> splitted_command);

    //--------------------------------------------------------------------------
    // Show command method
    // Show Command has been entered
    // @param splitted_command the command splitted by whitespace
    //
    void showCommandSelected(vector<string> splitted_command);

    //--------------------------------------------------------------------------
    // Reset command method
    // Reset Command has been entered
    // @param splitted_command the command splitted by whitespace
    //
    void resetCommandSelected(vector<string> splitted_command);

    //--------------------------------------------------------------------------
    // Move command method
    // Move Command has been entered
    // @param splitted_command the command splitted by whitespace
    //
    void moveCommandSelected(vector<string> splitted_command);

    //--------------------------------------------------------------------------
    // Fast Move command method
    // Fast Move Command has been entered
    // @param splitted_command the command splitted by whitespace
    //
    void fastMoveCommandSelected(vector<string> splitted_command);

    //--------------------------------------------------------------------------
    // Save command method
    // Save Command has been entered
    // @param splitted_command the command splitted by whitespace
    //
    void saveCommandSelected(vector<string> splitted_command);

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
    // Variable representing the show more command
    //
    static const string MORE_COMMAND;
  
    //--------------------------------------------------------------------------
    // One Way up
    //
    static const char ONE_WAY_UP;

    //--------------------------------------------------------------------------
    // One Way down
    //
    static const char ONE_WAY_DOWN;

    //--------------------------------------------------------------------------
    // One Way left
    //
    static const char ONE_WAY_LEFT;

    //--------------------------------------------------------------------------
    // One Way right
    //
    static const char ONE_WAY_RIGHT;

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
    // Show Method
    // Shows the current maze
    // @return the result of the executed command
    //
    int showMaze();

    //--------------------------------------------------------------------------
    // Show More Method
    // Shows the current maze with more infos
    // @return the result of the executed command
    //
    int showExtendedMaze();

    //--------------------------------------------------------------------------
    // Save Method
    // Saves the current maze
    // @param filename Filename of the maze which should be save
    // @return the result of the executed command
    //
    int saveMaze(string filename);

    //--------------------------------------------------------------------------
    // Load Method
    // Loads the current maze
    // @param filename Filename of the maze which should be loaded
    // @return the result of the executed command
    //
    int loadMaze(string filename);

    //--------------------------------------------------------------------------
    // Move Method
    // Move the player in the given direction
    // @param direction Direction to move
    // @return the result of the executed command
    //
    int movePlayer(string direction);

    //--------------------------------------------------------------------------
    // Fast Move Method
    // Move the player in the given direction
    // @param directions Directions to move
    // @return the result of the executed command
    //
    int fastMovePlayer(string directions);

    //--------------------------------------------------------------------------
    // Reset Method
    // Resets the game
    // @return the result of the executed command
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

