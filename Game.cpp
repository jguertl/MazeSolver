//------------------------------------------------------------------------------
// Game.cpp
//
// Group: Group 10, study assistant: Daniel Ellmeier
//
// Authors: Peter Buerscher (1530750)
// Jakob Guertl (1530763)
//------------------------------------------------------------------------------
//

#include "Game.h"

//------------------------------------------------------------------------------
Game::Game()
{
}

//------------------------------------------------------------------------------
Game::Game(string loadfile, string savefile)
{
}

//------------------------------------------------------------------------------
Game::Game(const Game& orig)
{
}

//------------------------------------------------------------------------------
Game::~Game()
{

}

void Game::startGame()
{
  string line;
  running_=true;
  while(running_==true)
  {
      std::cout << "sep> ";
      getline(std::cin, line);

      if(line.compare("quit")==0)
      {
          running_=false;
      }
  }
}

bool Game::checkMoves(string moves)
{

}
