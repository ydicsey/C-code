#ifndef MAZE_H
#define MAZE_H

#include <string>
#include <vector>
#include <iostream>

// for friend relation use
#include "robot.h"

using namespace std;

class maze
{
    vector<string> grid_;
    int height_;
    int width_;
    bool is_Obstacle( const int &x, const int &y ) const;
    friend void robot::move( const maze &Maze );
public:
    maze( const vector<string> &grid );
    maze( const vector<string> &grid, const int &height, const int &width );
    void print_maze() const;
    void print_maze_with_robot( const pair<int, int> &loc ) const;
};

#endif