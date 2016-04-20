//------------------------------------------------------------------------------
// main.cpp
//
// Group: Group 10, study assistant: Daniel Ellmeier
//
// Authors: Peter Buerscher (1530750)
// Jakob Guertl (1530763)
//------------------------------------------------------------------------------
//

#include <iostream>
#include <string>
#include "WrongUsageException.h"
#include "OutOfMemoryException.h"
#include "Game.h"
#include "StartGameCommand.h"
#include "FastMoveCommand.h"

using std::cout;
using std::endl;
using std::string;
using std::shared_ptr;
using std::make_shared;
using std::exception;

//------------------------------------------------------------------------------
// main function
// entry point for execution
// @param argc argument count
// @param **argv argument values
// @return return value for the OS
//
int main(int argc, char** argv) {
  static const int PROGRAM_EXIT_SUCCESS = 0;
  static const int PROGRAM_EXIT_ERROR = 1;
  static const int PROGRAM_EXIT_WRONG_USAGE = 2;
  static const string PROGRAM_ARGUMENT_INPUT = "-m";
  static const string PROGRAM_ARGUMENT_OUTPUT = "-s";
  
  try
  {
    Game game;
    shared_ptr<StartGameCommand> start_game_command;
    if(argc == 3 && string(argv[1]) == PROGRAM_ARGUMENT_INPUT)
    {
      game.setInputFilename(argv[2]);
    }
    else if(argc == 3 && string(argv[1]) == PROGRAM_ARGUMENT_OUTPUT)
    {
      game.setOutputFilename(argv[2]);
    }
    else if(argc == 5 && string(argv[1]) == PROGRAM_ARGUMENT_OUTPUT &&
      string(argv[3]) == PROGRAM_ARGUMENT_INPUT)
    {
      game.setInputFilename(argv[4]);
      game.setOutputFilename(argv[2]);
    }
    else if(argc == 5 && string(argv[1]) == PROGRAM_ARGUMENT_INPUT &&
      string(argv[3]) == PROGRAM_ARGUMENT_OUTPUT)
    {
      game.setInputFilename(argv[2]);
      game.setOutputFilename(argv[4]);
    }
    else if(argc != 1)
    {
      throw WrongUsageException();
    }
    start_game_command = make_shared<StartGameCommand>("New Game");
    vector<string> empty_parameters;
    start_game_command->execute(game, empty_parameters);
  }
  
  //Catch out of memory exception
  catch(OutOfMemoryException out_of_memory_exception)
  {
    return PROGRAM_EXIT_ERROR;
  }
  
  //Catch wrong usage exception
  catch(WrongUsageException wrong_usage_exception)
  {
    return PROGRAM_EXIT_WRONG_USAGE;
  }
  
  //Catch any other exception
  catch(exception other_exception)
  {
    return PROGRAM_EXIT_ERROR;
  }
  
  return PROGRAM_EXIT_SUCCESS;
}
