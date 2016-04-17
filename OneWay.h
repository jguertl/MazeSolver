//------------------------------------------------------------------------------
// OneWay.h
//
// Group: Group 10, study assistant: Daniel Ellmeier
//
// Authors: Peter Buerscher (1530750)
// Jakob Guertl (1530763)
//------------------------------------------------------------------------------
//

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

