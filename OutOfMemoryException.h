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

#include "BaseException.h"

//----------------------------------------------------------------------------
// Custom Out of Memory Exception
// class inform about bad memory allocation
//
class OutOfMemoryException : BaseException
{
    
public:
    
    //--------------------------------------------------------------------------
    // Constructor
    // Constructs the exception and outputs the error message.
    //
    OutOfMemoryException();
};

#endif //OUTOFMEMORYEXCEPTION