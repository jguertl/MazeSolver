/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Bonus.h
 * Author: Peter
 *
 * Created on 17. April 2016, 03:01
 */

#ifndef BONUS_H
#define BONUS_H

#include <string>
#include "Tile.h"

using std::string;

class Bonus : public Tile{
public:
    Bonus();
    Bonus(const Bonus& orig);
    virtual ~Bonus();
    virtual bool move(string direction) override;
private:

};

#endif /* BONUS_H */

