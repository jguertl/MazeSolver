//------------------------------------------------------------------------------
// WrongParameterCountException.h
//
// Group: Group 10, study assistant: Daniel Ellmeier
//
// Authors: Peter Buerscher (1530750)
// Jakob Guertl (1530763)
//------------------------------------------------------------------------------
//

#ifndef WRONGPARAMETERCOUNTEXCEPTION_H_INCLUDED
#define WRONGPARAMETERCOUNTEXCEPTION_H_INCLUDED

#include <string>
#include "BaseException.h"

using std::string;

//------------------------------------------------------------------------------
// Custom Wrong Parameter Count Exception
// class inform about a wrong parameter count
//
class WrongParameterCountException : public BaseException
{
  private:
    
    //--------------------------------------------------------------------------
    // Message to be shown in case of an exception
    //
    static const string WRONG_PARAMETER_COUNT_MESSAGE;
    
  public:
    
    //--------------------------------------------------------------------------
    // Constructor
    // Constructs the exception and outputs the error message.
    //
    WrongParameterCountException();
};

#endif //WRONGPARAMETERCOUNTEXCEPTION_H_INCLUDED