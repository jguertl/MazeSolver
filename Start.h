/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Start.h
 * Author: Peter
 *
 * Created on 17. April 2016, 02:50
 */

#ifndef START_H
#define START_H

#include <string>
#include "Tile.h"

using std::string;

class Start : public Tile{
public:
    Start();
    Start(const Start& orig);
    virtual ~Start();
    virtual bool move(string direction) override;
private:

};

#endif /* START_H */

