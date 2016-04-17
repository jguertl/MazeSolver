/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Ice.h
 * Author: Peter
 *
 * Created on 17. April 2016, 02:54
 */

#ifndef ICE_H
#define ICE_H

#include <string>
#include "Tile.h"

using std::string;

class Ice : public Tile{
public:
    Ice();
    Ice(const Ice& orig);
    virtual ~Ice();
    virtual bool move(string direction) override;
private:

};

#endif /* ICE_H */

