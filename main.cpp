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
#include "WrongUsageException.h"
#include "Game.h"
#include "StartGameCommand.h"

using std::cout;
using std::endl;

//------------------------------------------------------------------------------
// main function
// entry point for execution
// @param argc argument count
// @param **argv argument values
// @return return value for the OS
//
int main(int argc, char** argv) {
  Game game;
  StartGameCommand* startGameCommand = new StartGameCommand("New Game");
  std::vector<std::string> parameters;
  startGameCommand->execute(game, parameters);
  return 0;
}
