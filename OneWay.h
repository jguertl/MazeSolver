/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   OneWay.h
 * Author: Peter
 *
 * Created on 17. April 2016, 03:03
 */

#ifndef ONEWAY_H
#define ONEWAY_H

#include <string>
#include "Tile.h"

using std::string;

class OneWay : public Tile{
public:
    OneWay();
    OneWay(const OneWay& orig);
    virtual ~OneWay();
    virtual bool move(string direction) override;
private:

};

#endif /* ONEWAY_H */

