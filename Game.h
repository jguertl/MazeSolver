//------------------------------------------------------------------------------
// Game.h
//
// Group: Group 10, study assistant: Daniel Ellmeier
//
// Authors: Peter Buerscher (1530750)
// Jakob Guertl (1530763)
//------------------------------------------------------------------------------
//

#ifndef GAME_H
#define GAME_H

#include <string>
#include "Maze.h"
#include "Player.h"

using std::string;

class Game {
public:
    Game();
    Game(string loadfile, string savefile);
    Game(const Game& orig);
    virtual ~Game();
    Maze maze_;
    Player player_;
    void startGame();
private:

};

#endif /* GAME_H */

