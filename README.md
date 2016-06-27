# Maze Solver
This console program is a modified version of labyrinth challenges found in various RPG games. The aim of the game is to move the player towards the target destination of the maze. Mazes may contain special fields which help or hinder the player to solve the maze. Sometimes several difficult paths are available.  For a more detailed description, check out the original [specification](https://palme.iicm.tugraz.at/wiki/SEP).

![Image](https://s31.postimg.org/4ek24dmfv/maze.gif)

#### Features
* Find your way though any maze
* Pay attention to Teleport, Quicksand and OneWay fields
* Let AI solve your maze

#### Usage
    load <filename>
Loads a given maze.

    save <filename>
Saves the current maze.

    move <direction>
This command moves the player in the given direction.

    show [more]
Shows the current maze. The current player position is indicated as an asterisk. By using the optional command 'more' the remaining steps will be shown additionally.

    solve [silent]
This command solves the maze from the current player position. In silent mode, the winning path will not be printed.

#### Implementation Details
* Object-oriented design
* Command Design Pattern
* Shortest Path using Dijkstra's Algorithm

#### Contributors
* [Jakob Gürtl](https://github.com/jguertl)
* [Peter Bürscher](https://github.com/petbuer)
