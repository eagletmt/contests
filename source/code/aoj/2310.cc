#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct point
{
  int n, d;
  bool inc;
  point(int x, int y, bool z) : n(x), d(y), inc(z) {}
  bool operator<(const point& that) const
  {
    const int x = n*that.d;
    const int y = that.n*d;
    if (x == y) {
      return !inc && that.inc;
    } else {
      return x < y;
    }
  }
};

int main()
{
  int H, W;
  cin >> H >> W;
  vector<string> grid(H);
  for (int i = 0; i < H; i++) {
    cin >> grid[i];
  }

  vector<point> ps;
  for (int i = 0; i < H; i++) {
    for (int j = 0; j < W; j++) {
      if (grid[i][j] == '#'
          && (i == 0 || grid[i-1][j] == '.')
          && (j == 0 || grid[i][j-1] == '.')) {
        ps.push_back(point(j, H-i, true));
      } else if (grid[i][j] == '#'
          && (i == H-1 || grid[i+1][j] == '.')
          && (j == W-1 || grid[i][j+1] == '.')) {
        ps.push_back(point(j+1, H-i-1, false));
      } else if (grid[i][j] == '.'
          && (i != 0 && grid[i-1][j] == '#')
          && (j != 0 && grid[i][j-1] == '#')) {
        ps.push_back(point(j, H-i, true));
      } else if (grid[i][j] == '.'
          && (i != H-1 && grid[i+1][j] == '#')
          && (j != W-1 && grid[i][j+1] == '#')) {
        ps.push_back(point(j+1, H-i-1, false));
      }
    }
  }
  sort(ps.begin(), ps.end());
  int ans = 0;
  int acc = 1;
  for (vector<point>::const_iterator it = ps.begin(); it != ps.end(); ++it) {
    if (it->inc) {
      ++acc;
      ans = max(ans, acc);
    } else {
      --acc;
    }
  }
  cout << ans << endl;
  return 0;
}
