#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <map>

#include "maze.h"
#include "robot.h"

using namespace std;

int main()
{
    /**
    * Auto-generated code below aims at helping you parse
    * the standard input according to the problem statement.
    **/ 
    int width;
    int height;
    cin >> width >> height; cin.ignore();
    long long MAX_steps;
    cin >> MAX_steps; cin.ignore();

    pair<int , int> init(-1, -1);

    vector<string> map(height);
    for (int i = 0; i < height; i++) 
    {
        // string line;
        getline(cin, map[i]);
        for(int j = 0; j < width; j++)
        {
            if(map[i][j] == 'O' && init.first == -1)
            {
                map[i][j] = '.';
                init = make_pair(j ,i);
            }
        }
    }

    // create a maze
    maze Maze(map);
    map.clear();

    // create a robot
    robot Robot(init);

    long long cycle_len = 0, step = 1, stepID;

    while(step <= MAX_steps)
    {
        stepID = Robot.get_history_stepID();
        cycle_len = step - stepID;
        if(stepID != -1 && ((MAX_steps - step +1) % cycle_len) == 0)
        {
            cerr << "cycle length: " << cycle_len << "\n" << endl;
            break;
        }
        Robot.set_history_stepID(step);
        step ++;
        Robot.move(Maze);
    }
    cout << Robot.get_loc().first << " " << Robot.get_loc().second << endl;
}