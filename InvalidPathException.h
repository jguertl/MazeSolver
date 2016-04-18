//------------------------------------------------------------------------------
// InvalidPathException.h
//
// Group: Group 10, study assistant: Daniel Ellmeier
//
// Authors: Peter Buerscher (1530750)
// Jakob Guertl (1530763)
//------------------------------------------------------------------------------
//

#ifndef INVALIDPATHEXCEPTION_H_INCLUDED
#define INVALIDPATHEXCEPTION_H_INCLUDED

#include <string>
#include "BaseException.h"

using std::string;

//----------------------------------------------------------------------------
// Custom File Open Exception
// class inform about a file which cannot be openend
//
class InvalidPathException : BaseException
{
private:
  
  //--------------------------------------------------------------------------
  // Message to be shown in case of an exception
  //
  static const string InvalidPathMessage;
  
public:
  
  //--------------------------------------------------------------------------
  // Constructor
  // Constructs the exception and outputs the error message.
  //
  InvalidPathException();
};

#endif //INVALIDPATHEXCEPTION_H_INCLUDED