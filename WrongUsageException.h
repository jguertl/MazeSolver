//------------------------------------------------------------------------------
// WrongUsageException.h
//
// Group: Group 10, study assistant: Daniel Ellmeier
//
// Authors: Peter Buerscher (1530750)
// Jakob Guertl (1530763)
//------------------------------------------------------------------------------
//

#ifndef WRONGUSAGEEXCEPTION_H_INCLUDED
#define WRONGUSAGEEXCEPTION_H_INCLUDED

#include "BaseException.h"

//----------------------------------------------------------------------------
// Custom Wrong Usage Exception
// class inform about invalid arguments
//
class WrongUsageException : BaseException
{
        
  public:
        
  //--------------------------------------------------------------------------
  // Constructor
  // Constructs the exception and outputs the error message.
  //
  WrongUsageException();
};

#endif //WRONGUSAGEEXCEPTION_H_INCLUDED