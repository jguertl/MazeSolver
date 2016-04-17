/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Finish.h
 * Author: Peter
 *
 * Created on 17. April 2016, 02:52
 */

#ifndef FINISH_H
#define FINISH_H

#include <string>
#include "Tile.h"

using std::string;

class Finish : public Tile{
public:
    Finish();
    Finish(const Finish& orig);
    virtual ~Finish();
    virtual bool move(string direction) override;
private:

};

#endif /* FINISH_H */

