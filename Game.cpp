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
#include "LoadCommand.h"
#include "ResetCommand.h"
#include "MoveCommand.h"
#include "FastMoveCommand.h"
#include "ShowCommand.h"
#include "ShowMoreCommand.h"
#include "SaveCommand.h"
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
const string Game::SAVE_COMMAND = "save";
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

    //Change to lower case
    for(char& letter : command)
    {
      letter = tolower(letter);
    }

    try
    {
      if(command == Game::QUIT_COMMAND)
      {
        if(splitted_commands.size() > 1)
          throw WrongParameterCountException();
        running_ = false;
        cout << Game::QUIT_TEXT << endl;
      }
      else if(command == Game::LOAD_COMMAND)
      {
        if(splitted_commands.size() > 2)
          throw WrongParameterCountException();

        LoadCommand* load_command = new LoadCommand("Load");
        load_command->execute(*this, splitted_commands);
      }
      else if(command == Game::SHOW_COMMAND)
      {
        if(splitted_commands.size() > 2)
          throw WrongParameterCountException();

        if(splitted_commands.size() == 1)
        {
          ShowCommand* show_command = new ShowCommand("Show");
          show_command->execute(*this, splitted_commands);
        }
        else
        {
          if(splitted_commands.at(1) == Game::MORE_COMMAND)
          {
            ShowMoreCommand* show_more_command = new ShowMoreCommand("Show More");
            show_more_command->execute(*this, splitted_commands);
          }
          else
            throw WrongParameterException();
        }
      }
      else if(command == Game::RESET_COMMAND)
      {
        if(splitted_commands.size() > 1)
          throw WrongParameterCountException();

        ResetCommand* reset_command = new ResetCommand("Reset");
        reset_command->execute(*this, splitted_commands);
      }
      else if(command == Game::MOVE_COMMAND)
      {
        if(splitted_commands.size() > 2)
          throw WrongParameterCountException();

        MoveCommand* move_command = new MoveCommand("Move");
        move_command->execute(*this, splitted_commands);
      }
      else if(command == Game::FASTMOVE_COMMAND)
      {
        if(splitted_commands.size() != 2)
          throw WrongParameterCountException();

        FastMoveCommand* fast_move_command = new FastMoveCommand("Fastmove");
        fast_move_command->execute(*this, splitted_commands);
      }
      else if(command == Game::SAVE_COMMAND)
      {
        if(splitted_commands.size() != 2)
          throw WrongParameterCountException();

        SaveCommand* save_command = new SaveCommand("Save");
        save_command->execute(*this, splitted_commands);
      }
      else
      {
        throw UnknownCommandException();
      }
    }
    catch(UnknownCommandException unknown_command_exception)
    {
    }
    catch(WrongParameterCountException wrong_parameter_count_exception)
    {
    }
    catch(WrongParameterException wrong_parameter_exception)
    {
    }
    catch(NoMazeLoadedException no_maze_loaded_exception)
    {
    }
    catch(FileOpenException file_open_exception)
    {
    }
    catch(InvalidFileException invalid_file_exception)
    {
    }
    catch(InvalidPathException invalid_path_exception)
    {
    }
    catch(FileAccessException file_access_exception)
    {
    }
    catch(InvalidMoveException invalid_move_exception)
    {
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
  maze_.show();
  return 1;
}

//------------------------------------------------------------------------------
int Game::showExtendedMaze()
{
  maze_.showMore();
  return 1;
}

//------------------------------------------------------------------------------
int Game::saveMaze(string filename)
{
  maze_.save(filename);
  return 1;
}

//------------------------------------------------------------------------------
int Game::loadMaze(string filename)
{
  maze_.load(filename);
  return 1;
}

//------------------------------------------------------------------------------
int Game::movePlayer(string direction)
{
  maze_.movePlayer(direction);
  return 1;
}

//------------------------------------------------------------------------------
int Game::fastMovePlayer(string directions)
{
  maze_.fastMovePlayer(directions);
  return 1;
}

//------------------------------------------------------------------------------
int Game::reset()
{
  maze_.reset();
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

//------------------------------------------------------------------------------
vector<string> Game::splitString(string input, char delimiter)
{
  vector<string> splitted_strings;
  stringstream string_stream(input);
  string string_part;

  while(getline(string_stream, string_part, delimiter)) {
    splitted_strings.push_back(string_part);
  }

  return splitted_strings;
}
