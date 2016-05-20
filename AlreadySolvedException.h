//------------------------------------------------------------------------------
// AlreadySolvedException.h
//
// Group: Group 10, study assistant: Daniel Ellmeier
//
// Authors: Peter Buerscher (1530750)
// Jakob Guertl (1530763)
//------------------------------------------------------------------------------
//

#ifndef ALREADYSOLVEDEXCEPTION_H_INCLUDED
#define ALREADYSOLVEDEXCEPTION_H_INCLUDED

#include <string>
#include "BaseException.h"

using std::string;

//------------------------------------------------------------------------------
// Custom Already Solved Exception
// class to inform about an already solved maze
//
class AlreadySolvedException : public BaseException
{
private:
  
  //--------------------------------------------------------------------------
  // Message to be shown in case of an exception
  //
  static const string ALREADY_SOLVED_EXCEPTION;
  
public:
  
  //--------------------------------------------------------------------------
  // Constructor
  // Constructs the exception and outputs the error message.
  //
  AlreadySolvedException();
};

#endif //ALREADYSOLVEDEXCEPTION_H_INCLUDED
