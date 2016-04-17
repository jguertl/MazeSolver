/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Tile.h
 * Author: Peter
 *
 * Created on 17. April 2016, 02:41
 */

#ifndef TILE_H
#define TILE_H

#include <string>

using std::string;

class Tile {
public:
    Tile();
    Tile(const Tile& orig);
    virtual ~Tile();
    virtual bool move(string direction)=0;
private:
    char symbol_;
};

#endif /* TILE_H */

