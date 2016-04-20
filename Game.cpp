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
#include "UnknownCommandException.h"

const string Game::DIRECTION_MOVE_UP = "up";
const string Game::DIRECTION_MOVE_DOWN = "down";
const string Game::DIRECTION_MOVE_RIGHT = "right";
const string Game::DIRECTION_MOVE_LEFT = "left";
const char Game::DIRECTION_FAST_MOVE_UP = 'u';
const char Game::DIRECTION_FAST_MOVE_DOWN = 'd';
const char Game::DIRECTION_FAST_MOVE_RIGHT = 'r';
const char Game::DIRECTION_FAST_MOVE_LEFT = 'l';

//------------------------------------------------------------------------------
Game::Game()
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

//------------------------------------------------------------------------------
void Game::startGame()
{
  string line;
  running_=true;
  while(running_==true)
  {
    std::cout << "sep> ";
    getline(std::cin, line);
    
    //TODO zu switch case umschreiben
    if(line.compare("quit")==0)
    {
      running_=false;
      std::cout << "Bye!" << std::endl;
    }
    else if(line == "")
    {
      continue;
    }
    else
    {
      throw UnknownCommandException();
    }
  }
}

//------------------------------------------------------------------------------
bool Game::checkMoves(string moves)
{
  return true;
}

//------------------------------------------------------------------------------
int Game::showMaze()
{
  return 1;
}

//------------------------------------------------------------------------------
int Game::saveMaze(string filename)
{
  //TODO Throw FileAccessException here or inside Maze
  return 1;
}

//------------------------------------------------------------------------------
int Game::loadMaze(string filename)
{
  //TODO Throw FileOpenException / InvalidFileException / InvalidPathException
  // here or inside Maze
  return 1;
}

//------------------------------------------------------------------------------
int Game::movePlayer(string direction)
{
  return 1;
}

//------------------------------------------------------------------------------
int Game::fastMovePlayer(string directions)
{
  return 1;
}

//------------------------------------------------------------------------------
int Game::reset()
{
  return 1;
}

//------------------------------------------------------------------------------
void Game::setInputFilename(string input_filename)
{
  inputFilename_ = input_filename;
  loadMaze(inputFilename_);
}

//------------------------------------------------------------------------------
void Game::setOutputFilename(string output_filename)
{
  outputFilename_ = output_filename;
  autoSaveEnabled_ = true;
}

//------------------------------------------------------------------------------
bool Game::isMazeLoaded()
{
  return is_maze_loaded_;
}


