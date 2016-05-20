//------------------------------------------------------------------------------
// NoPathFoundException.h
//
// Group: Group 10, study assistant: Daniel Ellmeier
//
// Authors: Peter Buerscher (1530750)
// Jakob Guertl (1530763)
//------------------------------------------------------------------------------
//

#ifndef NOPATHFOUNDEXCEPTION_H_INCLUDED
#define NOPATHFOUNDEXCEPTION_H_INCLUDED

#include <string>
#include "BaseException.h"

using std::string;

//------------------------------------------------------------------------------
// Custom No Path Found Exception
// class to inform about an unsolvable maze
//
class NoPathFoundException : public BaseException
{
private:
  
  //--------------------------------------------------------------------------
  // Message to be shown in case of an exception
  //
  static const string NO_PATH_FOUND_EXCEPTION;
  
public:
  
  //--------------------------------------------------------------------------
  // Constructor
  // Constructs the exception and outputs the error message.
  //
  NoPathFoundException();
};

#endif //NOPATHFOUNDEXCEPTION_H_INCLUDED
