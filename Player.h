/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Player.h
 * Author: Peter
 *
 * Created on 17. April 2016, 03:15
 */

#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include "Tile.h"

using std::string;

class Player {
public:
    Player();
    Player(const Player& orig);
    virtual ~Player();
    void move(string direction);
    bool checkMoves(string moves);
private:
    int x_;
    int y_;
    Tile tile_;
};

#endif /* PLAYER_H */

