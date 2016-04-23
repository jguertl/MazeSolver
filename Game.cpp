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
#include "SaveCommand.h"
#include "MoveCommand.h"
#include "UnknownCommandException.h"
#include "WrongParameterCountException.h"
#include "WrongParameterException.h"
#include "UnknownCommandException.h"
#include "NoMazeLoadedException.h"
#include "InvalidMoveException.h"
#include "FileOpenException.h"
#include "InvalidFileException.h"
#include "InvalidPathException.h"
#include "FileAccessException.h"
#include "FileAccessException.h"
#include "NoMoreStepsException.h"
#include "LoadCommand.h"
#include "ResetCommand.h"
#include "MoveCommand.h"
#include "FastMoveCommand.h"
#include "ShowCommand.h"
#include "ShowMoreCommand.h"
#include "memory"
#include <sstream>
#include <iostream>

using std::cout;
using std::shared_ptr;
using std::make_shared;
using std::cin;
using std::stringstream;
using std::tolower;

const string Game::QUIT_COMMAND = "quit";
const string Game::LOAD_COMMAND = "load";
const string Game::SHOW_COMMAND = "show";
const string Game::RESET_COMMAND = "reset";
const string Game::MOVE_COMMAND = "move";
const string Game::MORE_COMMAND = "more";
const string Game::FASTMOVE_COMMAND = "fastmove";
const string Game::SAVE_COMMAND = "save";
const string Game::PROMPT_TEXT = "sep> ";
const string Game::QUIT_TEXT = "Bye!";
const string Game::DIRECTION_MOVE_UP = "up";
const string Game::DIRECTION_MOVE_DOWN = "down";
const string Game::DIRECTION_MOVE_RIGHT = "right";
const string Game::DIRECTION_MOVE_LEFT = "left";
const string Game::OUTPUT_MAZE_SOLVED = "Congratulation! You solved the maze.";
const char Game::ONE_WAY_UP = '^';
const char Game::ONE_WAY_DOWN = 'v';
const char Game::ONE_WAY_LEFT = '<';
const char Game::ONE_WAY_RIGHT = '>';
const char Game::DIRECTION_FAST_MOVE_UP = 'u';
const char Game::DIRECTION_FAST_MOVE_DOWN = 'd';
const char Game::DIRECTION_FAST_MOVE_RIGHT = 'r';
const char Game::DIRECTION_FAST_MOVE_LEFT = 'l';
const int Game::SUCCESS = 0;

//------------------------------------------------------------------------------
Game::Game()
{
  auto_save_enabled_ = false;
  is_maze_loaded_ = false;
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
  string command;
  running_ = true;

  while(running_ == true)
  {
    cout << Game::PROMPT_TEXT;
    getline(cin, line);

    if(line == "")
    {
      continue;
    }
    vector<string> splitted_commands = splitString(line, ' ');
    command = splitted_commands.at(0);
    command = toLowercase(command);

    try
    {
      if(command == Game::QUIT_COMMAND)
      {
        quitCommandSelected(splitted_commands);
      }
      else if(command == Game::LOAD_COMMAND)
      {
        loadCommandSelected(splitted_commands);
      }
      else if(command == Game::SHOW_COMMAND)
      {
        showCommandSelected(splitted_commands);
      }
      else if(command == Game::RESET_COMMAND)
      {
        resetCommandSelected(splitted_commands);
      }
      else if(command == Game::MOVE_COMMAND)
      {
        moveCommandSelected(splitted_commands);
      }
      else if(command == Game::FASTMOVE_COMMAND)
      {
        fastMoveCommandSelected(splitted_commands);
      }
      else if(command == Game::SAVE_COMMAND)
      {
        saveCommandSelected(splitted_commands);
      }
      else
      {
        throw UnknownCommandException();
      }
    }
    catch(UnknownCommandException unknown_command_exception)
    {
      continue;
    }
    catch(WrongParameterCountException wrong_parameter_count_exception)
    {
      continue;
    }
    catch(WrongParameterException wrong_parameter_exception)
    {
      continue;
    }
    catch(NoMazeLoadedException no_maze_loaded_exception)
    {
      continue;
    }
    catch(FileOpenException file_open_exception)
    {
      continue;
    }
    catch(InvalidFileException invalid_file_exception)
    {
      continue;
    }
    catch(InvalidPathException invalid_path_exception)
    {
      continue;
    }
    catch(FileAccessException file_access_exception)
    {
      continue;
    }
    catch(InvalidMoveException invalid_move_exception)
    {
      continue;
    }
    catch(NoMoreStepsException no_more_steps_exception)
    {
      handleNoMoreSteps();
    }
  }
}

//------------------------------------------------------------------------------
int Game::showMaze()
{
  maze_.show();
  return SUCCESS;
}

//------------------------------------------------------------------------------
int Game::showExtendedMaze()
{
  maze_.showMore();
  return SUCCESS;
}

//------------------------------------------------------------------------------
int Game::saveMaze(string filename)
{
  maze_.save(filename);
  return SUCCESS;
}

//------------------------------------------------------------------------------
int Game::loadMaze(string filename)
{
  return maze_.load(filename);
}

//------------------------------------------------------------------------------
int Game::movePlayer(string direction)
{
  return maze_.movePlayer(direction);
}

//------------------------------------------------------------------------------
int Game::fastMovePlayer(string directions)
{
  return maze_.fastMovePlayer(directions);
}

//------------------------------------------------------------------------------
int Game::reset()
{
  maze_.reset();
  return SUCCESS;
}

//------------------------------------------------------------------------------
void Game::setInputFilename(string input_filename)
{
  try
  {
    vector<string> load_input;
    load_input.push_back(LOAD_COMMAND);
    load_input.push_back(input_filename);
    loadCommandSelected(load_input);
  }
  catch(FileOpenException file_open_exception)
  {
    return;
  }
  catch(InvalidFileException invalid_file_exception)
  {
    return;
  }
  catch(InvalidPathException invalid_path_exception)
  {
    return;
  }
}

//------------------------------------------------------------------------------
void Game::setOutputFilename(string output_filename)
{
  output_filename_ = output_filename;
  auto_save_enabled_ = true;
}

//------------------------------------------------------------------------------
bool Game::isMazeLoaded()
{
  return is_maze_loaded_;
}

//------------------------------------------------------------------------------
vector<string> Game::splitString(string input, char delimiter)
{
  vector<string> splitted_strings;
  stringstream string_stream(input);
  string string_part;

  while(getline(string_stream, string_part, delimiter))
  {
    if(string_part.empty() == false)
    {
      splitted_strings.push_back(string_part);
    }
  }

  return splitted_strings;
}

//------------------------------------------------------------------------------
string Game::toLowercase(string command)
{
  for(char& letter : command)
  {
    letter = tolower(letter);
  }
  return command;
}

//------------------------------------------------------------------------------
void Game::handleNoMoreSteps()
{
  try
  {
    vector<string> reset_command = {RESET_COMMAND};
    resetCommandSelected(reset_command);
  }
  catch(FileAccessException file_access_exception)
  {
    return;
  }
  catch(NoMazeLoadedException no_maze_loaded)
  {
    return;
  }
}

//------------------------------------------------------------------------------
void Game::quitCommandSelected(vector<string> splitted_commands)
{
  if(splitted_commands.size() > 1)
  {
    throw WrongParameterCountException();
  }
  running_ = false;
  maze_.deleteMaze();
  cout << Game::QUIT_TEXT << endl;
}

//------------------------------------------------------------------------------
void Game::loadCommandSelected(vector<string> splitted_commands)
{
  int maze_return_value;
  if(splitted_commands.size() != 2)
  {
    throw WrongParameterCountException();
  }

  LoadCommand load_command(splitted_commands.at(0));
  maze_return_value = load_command.execute(*this, splitted_commands);
 
  if(maze_return_value == SUCCESS)
  {
    is_maze_loaded_ = true;
  }
  
  if(maze_return_value == Maze::GAME_WON)
  {
    is_maze_loaded_ = true;
    cout << OUTPUT_MAZE_SOLVED << endl;
  }
}

//------------------------------------------------------------------------------
void Game::showCommandSelected(vector<string> splitted_commands)
{
  if(splitted_commands.size() > 2)
  {
    throw WrongParameterCountException();
  }

  if(splitted_commands.size() == 1)
  {
    ShowCommand show_command(splitted_commands.at(0));
    show_command.execute(*this, splitted_commands);
  }
  else
  {
    if(splitted_commands.at(1) == MORE_COMMAND)
    {
      ShowMoreCommand show_more_command(splitted_commands.at(0));
      show_more_command.execute(*this, splitted_commands);
    }
    else
    {
      throw WrongParameterException();
    }
  }
}

//------------------------------------------------------------------------------
void Game::resetCommandSelected(vector<string> splitted_commands)
{
  if(splitted_commands.size() > 1)
  {
    throw WrongParameterCountException();
  }

  ResetCommand reset_command(splitted_commands.at(0));
  reset_command.execute(*this, splitted_commands);

  if(auto_save_enabled_ == true)
  {
    splitted_commands.push_back(output_filename_);
    SaveCommand save_command(splitted_commands.at(0));
    save_command.execute(*this, splitted_commands);
  }
}

//------------------------------------------------------------------------------
void Game::moveCommandSelected(vector<string> splitted_commands)
{
  int maze_return_value;
  if(splitted_commands.size() != 2)
  {
    throw WrongParameterCountException();
  }

  MoveCommand move_command(splitted_commands.at(0));
  maze_return_value = move_command.execute(*this, splitted_commands);

  if(maze_return_value != SUCCESS && maze_return_value != Maze::GAME_WON)
  {
    throw InvalidMoveException();
  }

  if(auto_save_enabled_ == true)
  {
    splitted_commands.pop_back();
    splitted_commands.push_back(output_filename_);
    SaveCommand save_command(splitted_commands.at(0));
    save_command.execute(*this, splitted_commands);
  }

  ShowCommand show_command(splitted_commands.at(0));
  show_command.execute(*this, splitted_commands);
  
  if(maze_return_value == Maze::GAME_WON)
  {
    cout << OUTPUT_MAZE_SOLVED << endl;
  }
}

//------------------------------------------------------------------------------
void Game::fastMoveCommandSelected(vector<string> splitted_commands)
{
  int maze_return_value;
  if(splitted_commands.size() != 2)
  {
    throw WrongParameterCountException();
  }

  FastMoveCommand fast_move_command(splitted_commands.at(0));
  maze_return_value = fast_move_command.execute(*this, splitted_commands);

  if(auto_save_enabled_ == true)
  {
    splitted_commands.pop_back();
    splitted_commands.push_back(output_filename_);
    SaveCommand save_command(splitted_commands.at(0));
    save_command.execute(*this, splitted_commands);
  }

  ShowCommand show_command(splitted_commands.at(0));
  show_command.execute(*this, splitted_commands);

  if(maze_return_value == Maze::GAME_WON)
  {
    cout << OUTPUT_MAZE_SOLVED << endl;
  }
}

//------------------------------------------------------------------------------
void Game::saveCommandSelected(vector<string> splitted_commands)
{
  if(splitted_commands.size() != 2)
  {
    throw WrongParameterCountException();
  }

  SaveCommand save_command(splitted_commands.at(0));
  save_command.execute(*this, splitted_commands);
}
