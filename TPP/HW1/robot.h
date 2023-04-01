#ifndef ROBOT_H
#define ROBOT_H

#include <vector>
#include <iostream>

using namespace std;

// forward declaration
class maze;

class robot
{
    pair<int ,int> loc_;
    int dir;
    // memoized position instead of simulating the robot's movements again.
    // init with -1, means not visied by this dir
    // like memo[h][w][4]
    vector<vector<vector<int>>> memo_;
    void trun_90_degree();
    const int get_dir();
    const pair<int, int> next_loc() const;
    void set_loc( const pair<int, int> &loc );
public:
    robot();
    robot( const pair<int, int> &loc );
    void move( const maze &Maze );
    const int get_history_stepID() const;
    void set_history_stepID( const int &stepID );
    const pair<int , int> get_loc() const;
};

#endif