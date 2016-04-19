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

