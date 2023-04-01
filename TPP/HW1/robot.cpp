#include "robot.h"
#include "maze.h"

// public:
robot::robot()
{
    vector<vector<vector<int>>> memo(10, vector<vector<int>>(20, vector<int>(4, -1)));
    memo_ = memo;
    loc_ = make_pair(-1, -1);
    dir = 0;
    memo.clear();
}

robot::robot(const pair<int, int> &loc)
{
    vector<vector<vector<int>>> memo(10, vector<vector<int>>(20, vector<int>(4, -1)));
    memo_ = memo;
    dir = 0;
    loc_ = loc;
    memo.clear();
}

void robot::move( const maze &Maze )
{
    // store next postion: (x, y)
    pair<int, int> next_pos(-1, -1);
    while(1)
    {
        next_pos = make_pair(this->next_loc().first, this->next_loc().second);
        if(Maze.is_Obstacle(next_pos.second, next_pos.first))
        {
            this->trun_90_degree();
            continue;
        }
        this->set_loc(next_pos);
        break;
    }
}

const int robot::get_history_stepID() const
{
    return memo_[loc_.second][loc_.first][dir];
}

void robot::set_history_stepID( const int &stepID )
{
    memo_[loc_.second][loc_.first][dir] = stepID;
}

const pair<int , int> robot::get_loc() const
{
    const pair<int , int> ans = loc_;
    return ans;
}

// private:
void robot::trun_90_degree()
{
    dir = (dir+1) %4; 
}

const int robot::get_dir()
{
    return dir;
}

// return next step without obstacle determinded
const pair<int, int> robot::next_loc() const
{
    const pair<int,int> moves[4] {{0, -1}, {1, 0}, {0, 1}, {-1, 0}};

    const pair<int, int> ans(loc_.first+moves[dir].first, loc_.second + moves[dir].second);

    return ans;
}

void robot::set_loc( const pair<int, int> &loc )
{
    loc_ = make_pair(loc.first, loc.second);
}