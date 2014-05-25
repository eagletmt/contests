#include <iostream>
#include <vector>
#include <queue>
using namespace std;

int counter = 0;

void bfs(vector<vector<vector<int> > >& stamps, const vector<string>& grid, const pair<int,int>& start, const pair<int,int>& goal)
{
  const int R = grid.size(), C = grid[0].size();
  queue<pair<int,int> > q;
  q.push(start);
  vector<vector<int> > prev(R, vector<int>(C, -1));
  while (!q.empty()) {
    if (q.front() == goal) {
      break;
    }
    const int i = q.front().first;
    const int j = q.front().second;
    q.pop();

    for (int d = 0; d < 4; d++) {
      static const int di[] = {1, -1, 0, 0};
      static const int dj[] = {0, 0, 1, -1};
      const int k = i + di[d], l = j + dj[d];
      if (0 <= k && k < R && 0 <= l && l < C && grid[k][l] == '.' && prev[k][l] == -1) {
        prev[k][l] = i*C + j;
        q.push(make_pair(k, l));
      }
    }
  }
  vector<pair<int,int> > path;
  for (pair<int,int> pos = goal; pos != start;) {
    path.push_back(pos);
    const int p = prev[pos.first][pos.second];
    pos.first = p/C;
    pos.second = p%C;
  }
  for (vector<pair<int,int> >::reverse_iterator it = path.rbegin(); it != path.rend(); ++it) {
    stamps[it->first][it->second].push_back(counter++);
  }
}

int main()
{
  int R, C, M;
  cin >> R >> C >> M;
  vector<string> grid(R);
  for (int i = 0; i < R; i++) {
    cin >> grid[i];
  }
  static int keep_costs[50][50], on_costs[50][50], off_costs[50][50];
  for (int i = 0; i < R; i++) {
    for (int j = 0; j < C; j++) {
      cin >> keep_costs[i][j];
    }
  }
  for (int i = 0; i < R; i++) {
    for (int j = 0; j < C; j++) {
      cin >> on_costs[i][j];
    }
  }
  for (int i = 0; i < R; i++) {
    for (int j = 0; j < C; j++) {
      cin >> off_costs[i][j];
    }
  }
  static pair<int,int> rooms[1000];
  for (int i = 0; i < M; i++) {
    cin >> rooms[i].first >> rooms[i].second;
  }

  vector<vector<vector<int> > > stamps(R, vector<vector<int> >(C));
  stamps[rooms[0].first][rooms[0].second].push_back(counter++);
  for (int i = 0; i < M-1; i++) {
    bfs(stamps, grid, rooms[i], rooms[i+1]);
  }
  int ans = 0;
  for (int i = 0; i < R; i++) {
    for (int j = 0; j < C; j++) {
      const vector<int>& s = stamps[i][j];
      if (!s.empty()) {
        const int keep = keep_costs[i][j];
        const int on = on_costs[i][j];
        const int off = off_costs[i][j];
        ans += on;
        for (vector<int>::const_iterator it = s.begin(); it+1 != s.end(); ++it) {
          ans += min(off + on, keep*(*(it+1) - *it));
        }
        ans += off;
      }
    }
  }
  cout << ans << endl;
  return 0;
}
