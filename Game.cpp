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

<<<<<<< HEAD
bool Game::checkMoves(string moves)
{

}
=======
//------------------------------------------------------------------------------
int Game::showMaze()
{
  return 1;
}

//------------------------------------------------------------------------------
int Game::saveMaze(string filename)
{
  return 1;
}

//------------------------------------------------------------------------------
int Game::loadMaze(string filename)
{
  return 1;
}

//------------------------------------------------------------------------------
int Game::movePlayer(string direction)
{
  return 1;
}
>>>>>>> origin/master
