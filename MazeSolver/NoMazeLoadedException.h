//------------------------------------------------------------------------------
// NoMazeLoadedException.h
//
// Group: Group 10, study assistant: Daniel Ellmeier
//
// Authors: Peter Buerscher (1530750)
// Jakob Guertl (1530763)
//------------------------------------------------------------------------------
//

#ifndef NOMAZELOADEDEXCEPTION_H_INCLUDED
#define NOMAZELOADEDEXCEPTION_H_INCLUDED

#include <string>
#include "BaseException.h"

using std::string;

//------------------------------------------------------------------------------
// Custom No Maze Loaded Exception
// class inform if a maze has been loaded
//
class NoMazeLoadedException : public BaseException
{
  private:
    
    //--------------------------------------------------------------------------
    // Message to be shown in case of an exception
    //
    static const string NO_MAZE_LOADED_MESSAGE;
    
  public:
    
    //--------------------------------------------------------------------------
    // Constructor
    // Constructs the exception and outputs the error message.
    //
    NoMazeLoadedException();
};

#endif //NOMAZELOADEDEXCEPTION_H_INCLUDED