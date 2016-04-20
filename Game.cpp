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
#include "LoadCommand.h"
#include "memory"

using std::cout;
using std::shared_ptr;
using std::make_shared;
using std::cin;

const string Game::QUIT_COMMAND = "quit";
const string Game::LOAD_COMMAND = "load";
const string Game::SHOW_COMMAND = "show";
const string Game::RESET_COMMAND = "reset";
const string Game::MOVE_COMMAND = "move";
const string Game::FASTMOVE_COMMAND = "fastmove";
const string Game::PROMPT_TEXT = "sep> ";
const string Game::QUIT_TEXT = "Bye!";
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
  running_ = true;
  
  while(running_ == true)
  {
    cout << Game::PROMPT_TEXT;
    getline(cin, line);

    if(line == Game::QUIT_COMMAND)
    {
      running_ = false;
      cout << Game::QUIT_TEXT << endl;
    }
    else if(line == Game::LOAD_COMMAND)
    {
      maze_.load("hello.txt");
    }
    else if(line == Game::SHOW_COMMAND)
    {
      maze_.show();
      maze_.showMore();
    }
    else if(line == Game::RESET_COMMAND)
    {
      //RESET
    }
    else if(line == Game::MOVE_COMMAND)
    {
      maze_.movePlayer("up");
    }
    else if(line == Game::FASTMOVE_COMMAND)
    {
      //FASTMOVE
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


