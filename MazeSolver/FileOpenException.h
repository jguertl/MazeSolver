//------------------------------------------------------------------------------
// FileOpenException.h
//
// Group: Group 10, study assistant: Daniel Ellmeier
//
// Authors: Peter Buerscher (1530750)
// Jakob Guertl (1530763)
//------------------------------------------------------------------------------
//

#ifndef FILEOPENEXCEPTION_H_INCLUDED
#define FILEOPENEXCEPTION_H_INCLUDED

#include <string>
#include "BaseException.h"

using std::string;

//------------------------------------------------------------------------------
// Custom File Open Exception
// class inform about a file which cannot be openend
//
class FileOpenException : public BaseException
{
  private:
    
    //--------------------------------------------------------------------------
    // Message to be shown in case of an exception
    //
    static const string FILE_OPEN_MESSAGE;
    
  public:
    
    //--------------------------------------------------------------------------
    // Constructor
    // Constructs the exception and outputs the error message.
    //
    FileOpenException();
};

#endif //FILEOPENEXCEPTION_H_INCLUDED