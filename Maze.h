//------------------------------------------------------------------------------
// Maze.h
//
// Group: Group 10, study assistant: Daniel Ellmeier
//
// Authors: Peter Buerscher (1530750)
// Jakob Guertl (1530763)
//------------------------------------------------------------------------------
//

#ifndef MAZE_H_INCLUDED
#define MAZE_H_INCLUDED

#include <string>
#include <vector>
#include "Player.h"
#include "Tile.h"
#include "Wall.h"
#include "Path.h"
#include "Ice.h"
#include "Start.h"
#include "Finish.h"
#include "Bonus.h"
#include "Quicksand.h"
#include "Teleport.h"
#include "OneWay.h"

class Game;

using std::string;
using std::vector;

//----------------------------------------------------------------------------
// Style Maze
// class to represent a maze
//
class Maze
{
  private:

    //--------------------------------------------------------------------------
    // minimum lowercase char allowed in filenames
    //
    static const char FILENAME_DEFINITION_LOWERCASE_MIN;

    //--------------------------------------------------------------------------
    // maximum lowercase char allowed in filenames
    //
    static const char FILENAME_DEFINITION_LOWERCASE_MAX;

    //--------------------------------------------------------------------------
    // minimum uppercase char allowed in filenames
    //
    static const char FILENAME_DEFINITION_UPPERCASE_MIN;

    //--------------------------------------------------------------------------
    // maximum uppercase char allowed in filenames
    //
    static const char FILENAME_DEFINITION_UPPERCASE_MAX;

    //--------------------------------------------------------------------------
    // minimum number allowed in filenames
    //
    static const char FILENAME_DEFINITION_NUMBER_MIN;

    //--------------------------------------------------------------------------
    // maximum number allowed in filenames
    //
    static const char FILENAME_DEFINITION_NUMBER_MAX;

    //--------------------------------------------------------------------------
    // special dot allowed in filenames
    //
    static const char FILENAME_DEFINITION_DOT;

    //--------------------------------------------------------------------------
    // special slash allowed in filenames
    //
    static const char FILENAME_DEFINITION_SLASH;

    //--------------------------------------------------------------------------
    // maximum filename length
    //
    static const int FILENAME_DEFINITION_LENGTH = 255;

    //--------------------------------------------------------------------------
    // output string naming the remaining steps
    //
    static const string OUTPUT_MOVED_STEPS;

    //--------------------------------------------------------------------------
    // output string naming the remaining steps
    //
    static const string OUTPUT_REMAINING_STEPS;

    //--------------------------------------------------------------------------
    // output string naming the finished game
    //
    static const string OUTPUT_MAZE_SOLVED;

    //--------------------------------------------------------------------------
    // name of the save-file for reset
    //
    static const string SAVE_FILE_NAME;

    //--------------------------------------------------------------------------
    // field of type player
    //
    static const char FAST_MOVE_FLAG;

    //--------------------------------------------------------------------------
    // field of type player
    //
    static const char FIELD_TYPE_PLAYER;

    //--------------------------------------------------------------------------
    // field of type wall
    //
    static const char FIELD_TYPE_WALL;

    //--------------------------------------------------------------------------
    // field of type path
    //
    static const char FIELD_TYPE_PATH;

    //--------------------------------------------------------------------------
    // field of type ice
    //
    static const char FIELD_TYPE_ICE;

    //--------------------------------------------------------------------------
    // field of type start
    //
    static const char FIELD_TYPE_START;

    //--------------------------------------------------------------------------
    // field of type finish
    //
    static const char FIELD_TYPE_FINISH;

    //--------------------------------------------------------------------------
    // field of type teleport minimum
    //
    static const char FIELD_TYPE_TELEPORT_MIN;

    //--------------------------------------------------------------------------
    // field of type teleport maximum
    //
    static const char FIELD_TYPE_TELEPORT_MAX;

    //--------------------------------------------------------------------------
    // field of type bonus minimum
    //
    static const char FIELD_TYPE_BONUS_MIN;

    //--------------------------------------------------------------------------
    // field of type bonus maximum
    //
    static const char FIELD_TYPE_BONUS_MAX;

    //--------------------------------------------------------------------------
    // field of type quicksand minimum
    //
    static const char FIELD_TYPE_QUICKSAND_MIN;

    //--------------------------------------------------------------------------
    // field of type quicksand maximum
    //
    static const char FIELD_TYPE_QUICKSAND_MAX;

    //--------------------------------------------------------------------------
    // field of type oneway up
    //
    static const char FIELD_TYPE_ONEWAY_UP;

    //--------------------------------------------------------------------------
    // field of type oneway down
    //
    static const char FIELD_TYPE_ONEWAY_DOWN;

    //--------------------------------------------------------------------------
    // field of type oneway left
    //
    static const char FIELD_TYPE_ONEWAY_LEFT;

    //--------------------------------------------------------------------------
    // field of type oneway right
    //
    static const char FIELD_TYPE_ONEWAY_RIGHT;

    //--------------------------------------------------------------------------
    // TODO
    //
    string moves_;

    //--------------------------------------------------------------------------
    // Current amount of steps
    //
    int steps_;

    //--------------------------------------------------------------------------
    // Original amount of steps
    //
    int original_steps_;

    //--------------------------------------------------------------------------
    // Current x Counter
    //
    int counter_x_;

    //--------------------------------------------------------------------------
    // Current y Counter
    //
    int counter_y_;

    //--------------------------------------------------------------------------
    // Player
    //
    Player player_;

    //--------------------------------------------------------------------------
    // Collection of tiles
    //
    vector< vector<Tile*> > tiles_;

  public:

    //--------------------------------------------------------------------------
    // Constructor
    //
    Maze();

    //--------------------------------------------------------------------------
    // Destructor
    //
    ~Maze();

    //--------------------------------------------------------------------------
    // Load Method
    // TODO description
    // @param path file path to load
    //
    void load(const string& path);

    //--------------------------------------------------------------------------
    // Save Method
    // TODO description
    // @param path file path to save
    //
    void save(const string& path);

    //--------------------------------------------------------------------------
    // Delete Maze
    // TODO description
    //
    void deleteMaze();

    //--------------------------------------------------------------------------
    // Show Maze
    // TODO description
    //
    void show();

    //--------------------------------------------------------------------------
    // Show More
    // TODO description
    //
    void showMore();

    //--------------------------------------------------------------------------
    // Move Player
    // TODO description
    //
    int movePlayer(string direction);

    //--------------------------------------------------------------------------
    // Move Player Fast
    // TODO description
    //
    int fastMovePlayer(string directions);

    //--------------------------------------------------------------------------
    // Move to the corresponding Teleport Tile
    // TODO description
    //
    int moveTeleport(char symbol);

    //--------------------------------------------------------------------------
    // Compare two characters
    // TODO description
    // @param symbol1
    // @param symbol2
    //
    bool compareCharacters(const char symbol1, const char symbol2);

    //--------------------------------------------------------------------------
    // Get Tile at Position
    // TODO description
    //
    Tile* getTile(int x, int y);

    //--------------------------------------------------------------------------
    // Get Player
    // TODO description
    //
    Player* getPlayer();

    //--------------------------------------------------------------------------
    // Getter Player x
    // TODO description
    // @return x x-value
    //
    int getPlayerX();

    //--------------------------------------------------------------------------
    // Setter Player x
    // TODO description
    // @param x x-value
    //
    void setPlayerX(int x);

    //--------------------------------------------------------------------------
    // Getter Player y
    // TODO description
    // @return y y-value
    //
    int getPlayerY();

    //--------------------------------------------------------------------------
    // Setter Player y
    // TODO description
    // @param y y-value
    //
    void setPlayerY(int y);

    //--------------------------------------------------------------------------
    // Filename Validation method
    // Checks wheter a filename is valid or not
    // @param filename the given filename
    //
    static bool isFilenameValid(string filename);
};

#endif //MAZE_H_INCLUDED

