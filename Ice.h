//------------------------------------------------------------------------------
// Ice.h
//
// Group: Group 10, study assistant: Daniel Ellmeier
//
// Authors: Peter Buerscher (1530750)
// Jakob Guertl (1530763)
//------------------------------------------------------------------------------
//

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

