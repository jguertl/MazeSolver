//------------------------------------------------------------------------------
// InvalidFileException.h
//
// Group: Group 10, study assistant: Daniel Ellmeier
//
// Authors: Peter Buerscher (1530750)
// Jakob Guertl (1530763)
//------------------------------------------------------------------------------
//

#ifndef INVALIDFILEEXCEPTION_H_INCLUDED
#define INVALIDFILEEXCEPTION_H_INCLUDED

#include <string>
#include "BaseException.h"

using std::string;

//----------------------------------------------------------------------------
// Custom File Open Exception
// class inform about an invalid file format
//
class InvalidFileException : BaseException
{
private:

  //--------------------------------------------------------------------------
  // Message to be shown in case of an exception
  //
  static const string INVALID_FILE_EXCEPTION;

public:

  //--------------------------------------------------------------------------
  // Constructor
  // Constructs the exception and outputs the error message.
  //
  InvalidFileException();
};

#endif //INVALIDFILEEXCEPTION_H_INCLUDED
