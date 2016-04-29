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

#include <string>
#include "BaseException.h"

using std::string;

//------------------------------------------------------------------------------
// Custom Wrong Usage Exception
// class to inform about invalid arguments
//
class WrongUsageException : public BaseException
{
  private:
  
    //--------------------------------------------------------------------------
    // Message to be shown in case of an exception
    //
    static const string WRONG_USAGE_MESSAGE;
  
  public:
        
    //--------------------------------------------------------------------------
    // Constructor
    // Constructs the exception and outputs the error message.
    //
    WrongUsageException();
};

#endif //WRONGUSAGEEXCEPTION_H_INCLUDED