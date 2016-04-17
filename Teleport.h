/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Teleport.h
 * Author: Peter
 *
 * Created on 17. April 2016, 02:56
 */

#ifndef TELEPORT_H
#define TELEPORT_H

#include <string>
#include "Tile.h"

using std::string;

class Teleport : public Tile{
public:
    Teleport();
    Teleport(const Teleport& orig);
    virtual ~Teleport();
    virtual bool move(string direction) override;
private:

};

#endif /* TELEPORT_H */

