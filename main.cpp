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
#include "Game.h"
#include "StartGameCommand.h"
#include "FastMoveCommand.h"

using std::cout;
using std::endl;
using std::string;
using std::shared_ptr;
using std::make_shared;

//------------------------------------------------------------------------------
// main function
// entry point for execution
// @param argc argument count
// @param **argv argument values
// @return return value for the OS
//
int main(int argc, char** argv) {
  try
  {
    Game game;
    shared_ptr<Command> start_game_command;
    if(argc == 3 && string(argv[1]) == "-m")
    {
      game.setInputFilename(argv[2]);
    }
    else if(argc == 3 && string(argv[1]) == "-s")
    {
      game.setOutputFilename(argv[2]);
    }
    else if(argc == 5 && string(argv[1]) == "-s" && string(argv[3]) == "-m")
    {
      game.setInputFilename(argv[4]);
      game.setOutputFilename(argv[2]);
    }
    else if(argc == 5 && string(argv[1]) == "-m" && string(argv[3]) == "-s")
    {
      game.setInputFilename(argv[2]);
      game.setOutputFilename(argv[4]);
    }
    else if(argc != 1)
    {
      throw WrongUsageException();
    }
    start_game_command = make_shared<Command>("New Game");
    vector<string> empty_parameters;
    start_game_command->execute(game, empty_parameters);
  }
  catch(WrongUsageException wrong_usage_exception)
  {
    return 2;
  }
  catch(...)
  {
    return 1;
  }
  return 0;
}
