/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Wall.h
 * Author: Peter
 *
 * Created on 17. April 2016, 02:43
 */

#ifndef WALL_H
#define WALL_H

#include <string>
#include "Tile.h"

using std::string;

class Wall : public Tile {
public:
    Wall();
    Wall(const Wall& orig);
    virtual ~Wall();
    virtual bool move(string direction) override;
private:

};

#endif /* WALL_H */

