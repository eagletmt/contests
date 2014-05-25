#include <iostream>
#include <vector>
#include <queue>
using namespace std;

struct state
{
  int man, box;
  string path;
  state(int m, int b, const string& p) : man(m), box(b), path(p) {}
};

struct in_range
{
  int lower, upper;
  in_range(int l, int u) : lower(l), upper(u) {}
  bool operator()(int x) const { return lower <= x && x < upper; }
};

bool bfs(const vector<string>& maze, int start, int goal, int box, string& path)
{
  const int R = maze.size();
  const int C = maze[0].size();
  const in_range r(0, R), c(0, C);

  queue<pair<string, int> > q;
  q.push(make_pair("", start));
  vector<vector<bool> > visited(R, vector<bool>(C, false));
  visited[start/C][start%C] = true;
  while (!q.empty()) {
    const pair<string, int> p = q.front();
    q.pop();
    if (p.second == goal) {
      path = p.first;
      return true;
    }
    for (int d = 0; d < 4; d++) {
      static const int di[] = {-1, 1, 0, 0}, dj[] = {0, 0, -1, 1};
      const int i = (p.second / C) + di[d];
      const int j = (p.second % C) + dj[d];
      if (r(i) && c(j) && i*C+j != box && maze[i][j] != '#' && !visited[i][j]) {
        static const char tbl[] = "nswe";
        visited[i][j] = true;
        q.push(make_pair(p.first + tbl[d], i*C+j));
      }
    }
  }
  return false;
}

string solve(const vector<string>& maze, int start, int goal, int box)
{
  const int R = maze.size();
  const int C = maze[0].size();
  const in_range r(0, R), c(0, C);

  queue<state> q;
  q.push(state(start, box, ""));
  vector<vector<bool> > visited(R, vector<bool>(C, false));
  visited[box/C][box%C] = true;
  while (!q.empty()) {
    const state s = q.front();
    q.pop();
    if (s.box == goal) {
      return s.path;
    }
    for (int d = 0; d < 4; d++) {
      static const int di[] = {-1, 1, 0, 0}, dj[] = {0, 0, -1, 1};
      const int i = (s.box / C) + di[d];
      const int j = (s.box % C) + dj[d];
      const int k = (s.box / C) - di[d];
      const int l = (s.box % C) - dj[d];
      if (r(i) && c(j) && r(k) && c(l) && maze[i][j] != '#' && maze[k][l] != '#' && !visited[i][j]) {
        string path;
        if (bfs(maze, s.man, k*C+l, s.box, path)) {
          visited[i][j] = true;
          static const char tbl[] = "NSWE";
          q.push(state(s.box, i*C+j, s.path + path + tbl[d]));
        }
      }
    }
  }
  return "Impossible.";
}

int main()
{
  for (int r, c, T = 1; cin >> r >> c && r != 0; ++T) {
    vector<string> maze(r);
    int start, goal, box;
    for (int i = 0; i < r; i++) {
      cin >> maze[i];
      for (int j = 0; j < c; j++) {
        if (maze[i][j] == 'S') {
          start = i*c + j;
          maze[i][j] = '.';
        } else if (maze[i][j] == 'T') {
          goal = i*c + j;
          maze[i][j] = '.';
        } else if (maze[i][j] == 'B') {
          box = i*c + j;
          maze[i][j] = '.';
        }
      }
    }
    cout << "Maze #" << T << endl;
    cout << solve(maze, start, goal, box) << endl;
    cout << endl;
  }
  return 0;
}
