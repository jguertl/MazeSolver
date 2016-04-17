//------------------------------------------------------------------------------
// Path.h
//
// Group: Group 10, study assistant: Daniel Ellmeier
//
// Authors: Peter Buerscher (1530750)
// Jakob Guertl (1530763)
//------------------------------------------------------------------------------
//

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

