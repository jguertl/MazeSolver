//------------------------------------------------------------------------------
// Maze.cpp
//
// Group: Group 10, study assistant: Daniel Ellmeier
//
// Authors: Peter Buerscher (1530750)
// Jakob Guertl (1530763)
//------------------------------------------------------------------------------
//

#include "Maze.h"
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

using std::ofstream;
using std::ifstream;
using std::string;
using std::cout;
using std::endl;

Maze::Maze() : steps_(0), moves_("") {
    cout << "Constructor 1" << endl;
}



Maze::~Maze() {
}

void Maze::loadMaze(const string& path){
    cout << "Load: " << path << endl;
    ifstream file ("maze.txt");
    string line;
    std::stringstream sstream;
    if (file.is_open())
    {
        std::getline(file, moves_);
        std::getline(file, line);
        sstream<<line;
        sstream>>steps_;
        sstream.str("");
        sstream.clear();
        
        while(std::getline(file, line))
        {
            tiles_.push_back(line);
        }
        
        file.close();
    }
    else
    {
        cout << "Unable to open file" ;
    }
    
    cout << "Moves: " << moves_ << endl;
    cout << "Steps: " << steps_ << endl;
    cout << "Size of Maze: " << tiles_.size() << endl;
    
    
}

void Maze::saveMaze(const string& path){
    cout << "Save" << endl;
}