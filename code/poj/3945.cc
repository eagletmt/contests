#include <iostream>
#include <queue>
#include <algorithm>
using namespace std;
static const int INF = 10000000;

struct cube
{
  int x, y, t, n, e, i;
  cube(int a, int b, int c, int d, int e_, int f)
    : x(a), y(b), t(c), n(d), e(e_), i(f)
  {}
  int top() const { return t; }
  int bottom() const { return t^1; }
  int north() const { return n; }
  int south() const { return n^1; }
  int east() const { return e; }
  int west() const { return e^1; }
  char color() const
  {
    static const char tbl[] = "rcgmby";
    return tbl[top()];
  }
};

int bfs(const vector<string>& grid, const string& route, int x, int y)
{
  const int H = grid.size();
  const int W = grid[0].size();
  static int dist[30][30][6][6][6];
  for (int i = 0; i < H; i++) {
    for (int j = 0; j < W; j++) {
      for (int t = 0; t < 6; t++) {
        for (int n = 0; n < 6; n++) {
          fill_n(dist[i][j][t][n], 6, INF);
        }
      }
    }
  }
  queue<cube> q;
  q.push(cube(x, y, 0, 2, 4, 0));
  dist[x][y][0][2][0] = 0;
  int ans = INF;
  while (!q.empty()) {
    const cube c = q.front();
    q.pop();
    const int dd = dist[c.x][c.y][c.t][c.n][c.i];
    for (int d = 0; d < 4; d++) {
      cube cc(c);
      static const int dx[] = {-1, 1, 0, 0}, dy[] = {0, 0, -1, 1};
      cc.x += dx[d];
      cc.y += dy[d];
      if (0 <= cc.x && cc.x < H && 0 <= cc.y && cc.y < W && grid[cc.x][cc.y] != 'k') {
        switch (d) {
          case 0: // north
            cc.n = c.top();
            cc.t = c.south();
            break;
          case 1: // south
            cc.n = c.bottom();
            cc.t = c.north();
            break;
          case 2: // west
            cc.e = c.bottom();
            cc.t = c.east();
            break;
          case 3: // east
            cc.e = c.top();
            cc.t = c.west();
            break;
        }
        if (grid[cc.x][cc.y] != 'w') {
          if (grid[cc.x][cc.y] == route[cc.i] && grid[cc.x][cc.y] == cc.color()) {
            ++cc.i;
            if (cc.i == 6) {
              ans = min(ans, dd+1);
            } else {
              int& ddd = dist[cc.x][cc.y][cc.t][cc.n][cc.i];
              if (dd+1 < ddd) {
                ddd = dd+1;
                q.push(cc);
              }
            }
          }
        } else {
          int& ddd = dist[cc.x][cc.y][cc.t][cc.n][cc.i];
          if (dd+1 < ddd) {
            ddd = dd+1;
            q.push(cc);
          }
        }
      }
    }
  }
  return ans;
}

int main()
{
  ios::sync_with_stdio(false);
  int W, H;
  while (cin >> W >> H && W != 0) {
    vector<string> grid(H);
    int x, y;
    for (int i = 0; i < H; i++) {
      cin >> grid[i];
      for (int j = 0; j < W; j++) {
        if (grid[i][j] == '#') {
          x = i;
          y = j;
          grid[i][j] = 'w';
        }
      }
    }
    string route;
    cin >> route;

    const int ans = bfs(grid, route, x, y);
    if (ans == INF) {
      cout << "unreachable" << endl;
    } else {
      cout << ans << endl;
    }
  }
  return 0;
}
