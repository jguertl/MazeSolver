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
#include <memory>

#include <vector>
#include <list>
#include <limits>
#include <set>
#include <utility>
#include <iterator>

class Player;
class Game;

using std::string;
using std::vector;
using std::unique_ptr;


// from: http://rosettacode.org/wiki/Dijkstra%27s_algorithm#C.2B.2B
// begin
typedef int vertex_t;
typedef double weight_t;
const weight_t max_weight_ = std::numeric_limits<double>::infinity();
struct neighbor {
    vertex_t target;
    weight_t weight;
    neighbor(vertex_t arg_target, weight_t arg_weight)
        : target(arg_target), weight(arg_weight) { }
};
typedef std::vector<std::vector<neighbor> > adjacency_list_t;
// end



//------------------------------------------------------------------------------
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
    static const int FILENAME_MAX_SIZE;

    //--------------------------------------------------------------------------
    // newline character
    //
    static const char NEW_LINE;

    //--------------------------------------------------------------------------
    // output string naming the remaining steps
    //
    static const string OUTPUT_MOVED_STEPS;

    //--------------------------------------------------------------------------
    // output string naming the remaining steps
    //
    static const string OUTPUT_REMAINING_STEPS;

    //--------------------------------------------------------------------------
    // name of the save-file for reset
    //
    static const string SAVE_FILE_NAME;

    //--------------------------------------------------------------------------
    // all numbers from 0 to 9 (used in validation)
    //
    static const string NUMBERS;

    //--------------------------------------------------------------------------
    // String which is appended to the filename to get the solved filename
    //
    static const string SOLVED_APPEND;

    //--------------------------------------------------------------------------
    // flag for fastmove identification in movePlayer
    //
    static const char FAST_MOVE_FLAG;

    //--------------------------------------------------------------------------
    // flag for ice identification in movePlayer
    //
    static const char ICE_MOVE_FLAG;

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
    // field of type hole
    //
    static const char FIELD_TYPE_HOLE;

    //--------------------------------------------------------------------------
    // field of type counter minimum
    //
    static const char FIELD_TYPE_COUNTER_MIN;

    //--------------------------------------------------------------------------
    // field of type counter maximum
    //
    static const char FIELD_TYPE_COUNTER_MAX;

    //--------------------------------------------------------------------------
    // the char '0' is used to convert from a char to an int number between 0
    // and 9
    //
    static const char COUNTER_ZERO_CHAR;

    //--------------------------------------------------------------------------
    // SOLVE_BONUS_CORRECTION is used to avoid negative costs in the dijkstra
    // algorithm
    //
    static const int SOLVE_BONUS_CORRECTION;

    //--------------------------------------------------------------------------
    // minimal value of a counter tile
    //
    static const int COUNTER_MIN_VALUE;

    //--------------------------------------------------------------------------
    // BONUS_OFFSET
    //
    static const int BONUS_OFFSET;

    //--------------------------------------------------------------------------
    // QUICKSAND_OFFSET
    //
    static const int QUICKSAND_OFFSET;

    //--------------------------------------------------------------------------
    // ERROR return value
    //
    static const int ERROR;

    //--------------------------------------------------------------------------
    // OUT_OF_STEPS return value
    //
    static const int OUT_OF_STEPS;

    //--------------------------------------------------------------------------
    // INVALID_MOVE return value
    //
    static const int INVALID_MOVE;

    //--------------------------------------------------------------------------
    // INVALID_PATH return value
    //
    static const int INVALID_PATH;

    //--------------------------------------------------------------------------
    // value 0 for initialization
    //
    static const int INITIALIZE_ZERO;

    //--------------------------------------------------------------------------
    // value -1 for initialization
    //
    static const int INITIALIZE_NEGATIVE;

    //--------------------------------------------------------------------------
    // current moves in fastmove-notation
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
    // ID of the start tile
    //
    int start_id_;

    //--------------------------------------------------------------------------
    // ID of the finish tile
    //
    int finish_id_;

    //--------------------------------------------------------------------------
    // fastmove string to solve the maze
    //
    string solved_path_;

    //--------------------------------------------------------------------------
    // step count of solve algorithm
    //
    int solved_steps_;

    //--------------------------------------------------------------------------
    // true if the adjacency list was already generated for this maze
    //
    bool is_adjacency_generated_;

    //--------------------------------------------------------------------------
    // Name of the current maze file
    //
    string filename_;

    //--------------------------------------------------------------------------
    // Player
    //
    Player player_;

    //--------------------------------------------------------------------------
    // vector for all ids of bonus tiles
    //
    vector<vertex_t> bonus_id_list;

    //--------------------------------------------------------------------------
    // Collection of tiles
    //
    vector<vector<unique_ptr<Tile>>> tiles_;

    //--------------------------------------------------------------------------
    // Twodimensional vector for the adjacencies
    //
    adjacency_list_t adjacency_list_;

  public:

    //--------------------------------------------------------------------------
    // GAME_WON return value
    //
    static const int GAME_WON;

    //--------------------------------------------------------------------------
    // SUCCESS return value
    //
    static const int SUCCESS;

    //--------------------------------------------------------------------------
    // Result of comparison between EQUAL operands
    //
    static const int EQUAL;

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
    // Loads the file path, checks if it is valid and calls fastmove.
    // @param path file path to load
    // @return int return value eg.: SUCCESS
    //
    int load(const string& path);

    //--------------------------------------------------------------------------
    // Save Method
    // Saves the current maze to a file.
    // @param path file path to save
    // @return int return value eg.: SUCCESS
    //
    int save(const string& path);

    //--------------------------------------------------------------------------
    // Delete Maze
    // Deletes all Tiles in the Maze and clears the vector tiles_ .
    // @return int return value eg.: SUCCESS
    //
    int deleteMaze();

    //--------------------------------------------------------------------------
    // Show Maze
    // Prints the current Maze to Stdout
    // @return int SUCCESS
    //
    int show();

    //--------------------------------------------------------------------------
    // Show More
    // Prints the current maze, the remaining steps and all past valid moves.
    // @param showPath true if the path should be printed
    // @return int SUCCESS
    //
    int showMore(bool showPath);

    //--------------------------------------------------------------------------
    // Solve
    // Solves the current maze
    // @param silent true if the path should not be printed
    // @return int SUCCESS
    //
    int solve(bool silent);

    //--------------------------------------------------------------------------
    // Generate Dijkstra Graph
    // Generates the Graph for the Dijkstra algorithm
    //
    void generateAdjacencyList();

    //--------------------------------------------------------------------------
    // Generate Path
    // Generates the fastmove-path from the given ID-path
    // @param path list containing the id path
    // @return string fastmove-path
    //
    string generatePath(std::list<vertex_t> path);

    //--------------------------------------------------------------------------
    // Reset Adjacency List
    // This function clears adjacency_list_
    // @return int SUCCESS or ERROR
    //
    int resetAdjacencyList();

    //--------------------------------------------------------------------------
    // Move Player
    // Moves the Player in the direction on the Maze
    // @param direction direction to move
    // @return int return value eg.: SUCCESS, INVALID_MOVE
    //
    int movePlayer(string direction);

    //--------------------------------------------------------------------------
    // Move Player Fast
    // Moves the Player a few steps in one command.
    // @param directions directions in fastmove-notation
    // @return int return value eg.: SUCCESS, INVALID_MOVE
    //
    int fastMovePlayer(string directions);

    //--------------------------------------------------------------------------
    // Move Player Fast Load
    // Moves the Player a few steps in one command and is only called in load.
    // @param directions directions in fastmove-notation
    // @return int return value eg.: SUCCESS, INVALID_MOVE
    //
    int fastMovePlayerLoad(string directions);

    //--------------------------------------------------------------------------
    // Move to the corresponding Teleport Tile
    // Moves the Player to the corresponding teleport tile.
    // @param symbol the character to which the Player should be teleported
    // @return int SUCCESS or ERROR
    //
    int moveTeleport(char symbol);

    //--------------------------------------------------------------------------
    // Get the ID of the corresponding Teleport-Tile
    // @param symbol the character of the teleport fields
    // @param cur_x x-position of the current teleport tile
    // @param cur_y y-position of the current teleport tile
    // @return int id of the other teleport field or ERROR
    //
    int getTeleportId(char symbol, int cur_x, int cur_y);

    //--------------------------------------------------------------------------
    // Reset Method
    // Loads the file again and the moves from the original file are reset.
    // @return int return value eg.: SUCCESS, ERROR
    //
    int reset();

    //--------------------------------------------------------------------------
    // Get Tile at Position
    // Get the Tile at a specific position in Maze.
    // @param x x-position of the Tile
    // @param y y-position of the Tile
    // @return char symbol of the Tile
    //
    char getTile(int x, int y);

    //--------------------------------------------------------------------------
    // Get Player
    // Getter for the player
    // @return Player* pointer to the player
    //
    Player* getPlayer();

    //--------------------------------------------------------------------------
    // Getter Player x
    // Getter for the x-value of the player
    // @return int x-value
    //
    int getPlayerX();

    //--------------------------------------------------------------------------
    // Setter Player x
    // Setter for the x-value of the player
    // @param x x-value
    //
    void setPlayerX(int x);

    //--------------------------------------------------------------------------
    // Getter Player y
    // Getter for the y-value of the player
    // @return int y-value
    //
    int getPlayerY();

    //--------------------------------------------------------------------------
    // Setter Player y
    // Setter for the y-value of the player
    // @param y y-value
    //
    void setPlayerY(int y);

    //--------------------------------------------------------------------------
    // Filename Validation method
    // Checks wether a filename is valid or not
    // @param filename the given filename
    //
    static bool isFilenameValid(string filename);
};

#endif //MAZE_H_INCLUDED

