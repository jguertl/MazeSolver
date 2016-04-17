/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Quicksand.h
 * Author: Peter
 *
 * Created on 17. April 2016, 03:04
 */

#ifndef QUICKSAND_H
#define QUICKSAND_H

#include <string>
#include "Tile.h"

using std::string;

class Quicksand : public Tile{
public:
    Quicksand();
    Quicksand(const Quicksand& orig);
    virtual ~Quicksand();
    virtual bool move(string direction) override;
private:

};

#endif /* QUICKSAND_H */

