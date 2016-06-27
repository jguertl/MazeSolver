//------------------------------------------------------------------------------
// UnknownCommandException.h
//
// Group: Group 10, study assistant: Daniel Ellmeier
//
// Authors: Peter Buerscher (1530750)
// Jakob Guertl (1530763)
//------------------------------------------------------------------------------
//

#ifndef UNKNOWNCOMMANDEXCEPTION_H_INCLUDED
#define UNKNOWNCOMMANDEXCEPTION_H_INCLUDED

#include <string>
#include "BaseException.h"

using std::string;

//------------------------------------------------------------------------------
// Custom Unknown Command Exception
// class inform about a unknown command
//
class UnknownCommandException : public BaseException
{
  private:
    
    //--------------------------------------------------------------------------
    // Message to be shown in case of an exception
    //
    static const string UNKNOWN_COMMAND_MESSAGE;
    
  public:
    
    //--------------------------------------------------------------------------
    // Constructor
    // Constructs the exception and outputs the error message.
    //
    UnknownCommandException();
};

#endif //UNKNOWNCOMMANDEXCEPTION_INCLUDED