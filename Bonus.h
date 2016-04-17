//------------------------------------------------------------------------------
// Bonus.h
//
// Group: Group 10, study assistant: Daniel Ellmeier
//
// Authors: Peter Buerscher (1530750)
// Jakob Guertl (1530763)
//------------------------------------------------------------------------------
//

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

