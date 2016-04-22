//------------------------------------------------------------------------------
// InvalidMoveException.h
//
// Group: Group 10, study assistant: Daniel Ellmeier
//
// Authors: Peter Buerscher (1530750)
// Jakob Guertl (1530763)
//------------------------------------------------------------------------------
//

#ifndef INVALIDMOVEEXCEPTION_H_INCLUDED
#define INVALIDMOVEEXCEPTION_H_INCLUDED

#include <string>
#include "BaseException.h"

using std::string;

//------------------------------------------------------------------------------
// Custom Invalid Move Exception
// class inform about a invalid move
//
class InvalidMoveException : BaseException
{
  private:
    
    //--------------------------------------------------------------------------
    // Message to be shown in case of an exception
    //
    static const string INVALID_MOVE_EXCEPTION;
    
  public:
    
    //--------------------------------------------------------------------------
    // Constructor
    // Constructs the exception and outputs the error message.
    //
    InvalidMoveException();
};

#endif //INVALIDMOVEEXCEPTION_H_INCLUDED