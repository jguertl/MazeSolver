/* 
 * File:   Maze.h
 * Author: Peter
 *
 * Created on 16. April 2016, 10:57
 */

#ifndef MAZE_H
#define MAZE_H
#include <string>
#include <vector>

using std::string;
using std::vector;

class Maze {
public:
    Maze();
    ~Maze();
    void loadMaze(const string& path);
    void saveMaze(const string& path);
private:
    string moves_;
    int steps_;
    int counter_;
    vector<string> tiles_;
    
    
    
};

#endif /* MAZE_H */

