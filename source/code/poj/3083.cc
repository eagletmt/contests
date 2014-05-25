#include <iostream>
#include <vector>
#include <queue>
using namespace std;

static const int UP = 0, RIGHT = 1, DOWN = 2, LEFT = 3;
static const int di[] = {-1, 0, 1, 0}, dj[] = {0, 1, 0, -1};

int hand(const vector<string>& maze, const pair<int,int>& p, int d, int which)
{
  int i = p.first, j = p.second;
  for (int c = 2; ; c++) {
    static const int a[] = {0, -1, 0, 1}, b[] = {-1, 0, 1, 0};
    i += di[d];
    j += dj[d];
    if (maze[i][j] == 'E') {
      return c;
    }
    if (maze[i+which*a[d]][j+which*b[d]] != '#') {
      d = (d - which + 4) % 4;
    } else if (maze[i+di[d]][j+dj[d]] != '#') {
      // do nothing
    } else if (maze[i-which*a[d]][j-which*b[d]] != '#') {
      d = (d + which + 4) % 4;
    } else {
      d = (d + 2) % 4;
    }
  }
}

int bfs(const vector<string>& maze, const pair<int,int>& start)
{
  const int H = maze.size();
  const int W = maze[0].size();
  vector<vector<int> > dist(H, vector<int>(W, 1000000));
  dist[start.first][start.second] = 1;
  queue<pair<int,int> > q;
  q.push(start);
  while (!q.empty()) {
    const int i = q.front().first;
    const int j = q.front().second;
    q.pop();
    if (maze[i][j] == 'E') {
      return dist[i][j];
    }
    for (int d = 0; d < 4; d++) {
      const int k = i + di[d];
      const int l = j + dj[d];
      if (0 <= k && k < H && 0 <= l && l < W && maze[k][l] != '#' && dist[i][j]+1 < dist[k][l]) {
        dist[k][l] = dist[i][j]+1;
        q.push(make_pair(k, l));
      }
    }
  }
  return -1;
}


int main()
{
  int T;
  cin >> T;
  while (T-- > 0) {
    int H, W;
    cin >> W >> H;
    vector<string> maze(H);
    pair<int,int> start;
    for (int i = 0; i < H; i++) {
      cin >> maze[i];
      for (int j = 0; j < W; j++) {
        if (maze[i][j] == 'S') {
          start = make_pair(i, j);
        }
      }
    }
    int dir;
    if (start.first == 0) {
      dir = DOWN;
    } else if (start.first == H-1) {
      dir = UP;
    } else if (start.second == 0) {
      dir = RIGHT;
    } else {
      dir = LEFT;
    }
    cout << hand(maze, start, dir, 1) << ' ' << hand(maze, start, dir, -1) << ' ' << bfs(maze, start) << endl;
  }
  return 0;
}
