#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

struct state
{
  int i, j, c, d;
  state(int x, int y, int z, int w) : i(x), j(y), c(z), d(w) {}
  bool operator<(const state& s) const { return d > s.d; }
};

int main()
{
  ios::sync_with_stdio(false);
  string line;
  while (getline(cin, line) && line != "--") {
    vector<string> grid;
    grid.push_back(line);
    while (getline(cin, line) && !line.empty()) {
      grid.push_back(line);
    }

    const int H = grid.size(), W = grid[0].size();
    static const int INF = 10000000;
    vector<vector<vector<int> > > dist(H, vector<vector<int> >(W, vector<int>(27, INF)));
    priority_queue<state> q;
    for (int i = 0; i < H; i++) {
      for (int j = 0; j < W; j++) {
        if (grid[i][j] == '$') {
          q.push(state(i, j, 26, 0));
          dist[i][j][26] = 0;
          break;
        }
      }
    }

    int ans = INF;
    while (!q.empty()) {
      const state s = q.top();
      q.pop();
      const int d = dist[s.i][s.j][s.c];
      if (d < s.d) {
        continue;
      }
      const char here = grid[s.i][s.j];
      if (here == '#') {
        if (s.c == 26) {
          ans = min(ans, d);
        }
        continue;
      } else if ('A' <= here && here <= 'Z') {
        if (here-'A'+1 >= 26-s.c) {
          ans = min(ans, d);
        }
        continue;
      }

      for (int k = 0; k < 4; k++) {
        static const int di[] = {-1, 1, 0, 0}, dj[] = {0, 0, -1, 1};
        const int i = s.i + di[k], j = s.j + dj[k];
        if ('1' <= grid[i][j] && grid[i][j] <= '9') {
          // w/ dynamite
          if (s.c > 0) {
            if (d < dist[i][j][s.c-1]) {
              dist[i][j][s.c-1] = d;
              q.push(state(i, j, s.c-1, d));
            }
          }

          // w/o dynamite
          const int dd = d + grid[i][j]-'0';
          if (dd < dist[i][j][s.c]) {
            dist[i][j][s.c] = dd;
            q.push(state(i, j, s.c, dd));
          }
        } else if (grid[i][j] != '*') {
          if (d < dist[i][j][s.c]) {
            dist[i][j][s.c] = d;
            q.push(state(i, j, s.c, d));
          }
        }
      }
    }

    if (ans == INF) {
      cout << "IMPOSSIBLE" << endl;
    } else {
      cout << ans << endl;
    }
  }
  return 0;
}
