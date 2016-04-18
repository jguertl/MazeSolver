//------------------------------------------------------------------------------
// WrongParameterException.h
//
// Group: Group 10, study assistant: Daniel Ellmeier
//
// Authors: Peter Buerscher (1530750)
// Jakob Guertl (1530763)
//------------------------------------------------------------------------------
//

#ifndef WRONGPARAMETEREXCEPTION_H_INCLUDED
#define WRONGPARAMETEREXCEPTION_H_INCLUDED

#include <string>
#include "BaseException.h"

using std::string;

//----------------------------------------------------------------------------
// Custom Wrong Parameter Exception
// class inform about a wrong parameter es
//
class WrongParameterException : BaseException
{
private:
  
  //--------------------------------------------------------------------------
  // Message to be shown in case of an exception
  //
  static const string WrongParameterMessage;
  
public:
  
  //--------------------------------------------------------------------------
  // Constructor
  // Constructs the exception and outputs the error message.
  //
  WrongParameterException();
};

#endif //WRONGPARAMETEREXCEPTION_H_INCLUDED