#include "maze.h"

maze::maze( const vector<string> &grid )
{
    grid_ = grid;
    width_ = grid[0].size();
    height_ = grid.size();
}

maze::maze( const vector<string> &grid, const int &height, const int &width )
{
    grid_ = grid;
    width_ = width;
    height_ = height;
}

void maze::print_maze() const
{
    cout << endl;
    for(int i = 0; i < height_; i++)
    {
        cout << grid_[i] << endl;
    }
}

void maze::print_maze_with_robot( const pair<int, int> &loc ) const
{
    cout << endl;
    for(int i = 0; i < height_; i++)
    {
        if(i == loc.second)
        {
            for(int j = 0; j < width_; j++)
            {
                if(j == loc.first)
                {
                    cout << 'O';
                }
                cout << grid_[i][j];
            }
            cout << endl;
        }
        else
        {
            cout << grid_[i] << endl;
        }
    }
}

bool maze::is_Obstacle( const int &x, const int &y ) const
{
    return (grid_[x][y] == '#');
}
