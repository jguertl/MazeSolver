//------------------------------------------------------------------------------
// OutOfMemoryException.h
//
// Group: Group 10, study assistant: Daniel Ellmeier
//
// Authors: Peter Buerscher (1530750)
// Jakob Guertl (1530763)
//------------------------------------------------------------------------------
//

#ifndef OUTOFMEMORYEXCEPTION_H_INCLUDED
#define OUTOFMEMORYEXCEPTION_H_INCLUDED

#include <string>
#include "BaseException.h"

using std::string;

//----------------------------------------------------------------------------
// Custom Out of Memory Exception
// class inform about bad memory allocation
//
class OutOfMemoryException : BaseException
{
  private:
  
    //--------------------------------------------------------------------------
    // Message to be shown in case of an exception
    //
    static const string OutOfMemoryMessage;
  
  public:
    
    //--------------------------------------------------------------------------
    // Constructor
    // Constructs the exception and outputs the error message.
    //
    OutOfMemoryException();
};

#endif //OUTOFMEMORYEXCEPTION_INCLUDED