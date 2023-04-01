#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

const int UP(0), RIGHT(1), DOWN(2), LEFT(3);
const pair<int,int> moves[4] {{0, -1}, {1, 0}, {0, 1}, {-1, 0}};

int main()
{
  vector<pair<int, int>> obstacles;
  pair<int, int> location;
  int direction = UP;
  int w, h;
  cin >> w >> h; cin.ignore();

  long long n;
  cin >> n; cin.ignore();

  cerr << w << " " << h << endl;
  cerr << n << endl;

  for (int i = 0; i < h; i++) 
  {
    string line;
    getline(cin, line);
    for(int j = 0; j < w; j++)
    {
      if(line[j] == '#') obstacles.emplace_back(j, i);
      if(line[j] == 'O') location = {j, i};
    }
  }

  vector<pair<int, int>> path;
  pair<int, int> initialLocation = location;

  bool firstRun = true;

  long long initN = n;    

  while(firstRun || (location != initialLocation))
  {
    if(n == 0) break;
    n--;
    firstRun = false;
    path.push_back(location);
    auto move = moves[direction];
    pair<int, int> nextLocation = { location.first + move.first, location.second + move.second };
    if(find(obstacles.begin(), obstacles.end(), nextLocation) != obstacles.end())
    {
      n++;
      direction = (direction + 1) % 4;
      move = moves[direction];
      nextLocation = { location.first + move.first, location.second + move.second };
      location = nextLocation;
    }
    else
    {
      location = nextLocation;
    }
  }

  cerr << "Path size is: " << path.size() << endl;
  for(const auto elem : path)
  {
    cerr << "(" << elem.first << ", " << elem.second << "), ";
  }
  cerr << endl;

  if(n == 0)
  {
  }
  else
  {
    location = path[initN % path.size()];
  }
  cout << location.first << " " << location.second << endl;
}

