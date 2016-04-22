//------------------------------------------------------------------------------
// NoMoreStepsException.h
//
// Group: Group 10, study assistant: Daniel Ellmeier
//
// Authors: Peter Buerscher (1530750)
// Jakob Guertl (1530763)
//------------------------------------------------------------------------------
//

#ifndef NOMORESTEPSEXCEPTION_H_INCLUDED
#define NOMORESTEPSEXCEPTION_H_INCLUDED

#include <string>
#include "BaseException.h"

using std::string;

//------------------------------------------------------------------------------
// Custom No More Steps Exception
// class inform that no more steps are available
//
class NoMoreStepsException : BaseException
{
  private:
    
    //--------------------------------------------------------------------------
    // Message to be shown in case of an exception
    //
    static const string NO_MORE_STEPS_MESSAGE;
    
  public:
    
    //--------------------------------------------------------------------------
    // Constructor
    // Constructs the exception and outputs the error message.
    //
    NoMoreStepsException();
};

#endif //NOMORESTEPSEXCEPTION_H_INCLUDED