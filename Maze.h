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
//#include "Game.h"

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
    // Show More
    // TODO description
    //
    int movePlayer(string direction);

    //--------------------------------------------------------------------------
    // Move to the corresponding Teleport Tile
    // TODO description
    //
    int moveTeleport(char symbol);

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
};

#endif //MAZE_H_INCLUDED

