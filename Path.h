/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Path.h
 * Author: Peter
 *
 * Created on 17. April 2016, 02:47
 */

#ifndef PATH_H
#define PATH_H

#include <string>
#include "Tile.h"

using std::string;

class Path : public Tile{
public:
    Path();
    Path(const Path& orig);
    virtual ~Path();
    virtual bool move(string direction) override;
private:

};

#endif /* PATH_H */

