/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Game.h
 * Author: Peter
 *
 * Created on 17. April 2016, 03:12
 */

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

