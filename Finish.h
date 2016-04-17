//------------------------------------------------------------------------------
// Finish.h
//
// Group: Group 10, study assistant: Daniel Ellmeier
//
// Authors: Peter Buerscher (1530750)
// Jakob Guertl (1530763)
//------------------------------------------------------------------------------
//

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

