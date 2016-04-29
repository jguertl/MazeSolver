//------------------------------------------------------------------------------
// FileAccessException.h
//
// Group: Group 10, study assistant: Daniel Ellmeier
//
// Authors: Peter Buerscher (1530750)
// Jakob Guertl (1530763)
//------------------------------------------------------------------------------
//

#ifndef FILEACCESSEXCEPTION_H_INCLUDED
#define FILEACCESSEXCEPTION_H_INCLUDED

#include <string>
#include "BaseException.h"

using std::string;

//------------------------------------------------------------------------------
// Custom File Access Exception
// class inform about invalid file access
//
class FileAccessException : public BaseException
{
  private:
    
    //--------------------------------------------------------------------------
    // Message to be shown in case of an exception
    //
    static const string FILE_ACCESS_EXCEPTION;
    
  public:
    
    //--------------------------------------------------------------------------
    // Constructor
    // Constructs the exception and outputs the error message.
    //
    FileAccessException();
};

#endif //FILEACCESSEXCEPTION_H_INCLUDED