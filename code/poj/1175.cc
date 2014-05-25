#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <iterator>
#include <set>
using namespace std;

static const char MARKED = '!';

set<pair<int,int> > rot(const set<pair<int,int> >& v, int H)
{
  set<pair<int,int> > ret;
  for (set<pair<int,int> >::const_iterator it = v.begin(); it != v.end(); ++it) {
    ret.insert(make_pair(it->second, H - it->first - 1));
  }
  return ret;
}

set<pair<int,int> > rev(const set<pair<int,int> >& v, int W)
{
  set<pair<int,int> > ret;
  for (set<pair<int,int> >::const_iterator it = v.begin(); it != v.end(); ++it) {
    ret.insert(make_pair(it->first, W - it->second - 1));
  }
  return ret;
}

struct cluster
{
  char name;
  int i, j;
  int W, H;
  set<pair<int,int> > v;

  bool same(const cluster& c) const
  {
    if ((H == c.H && W == c.W) || (H == c.W && W == c.H)) {
      set<pair<int,int> > tmp(v);
      int h = H, w = W;
      for (int k = 0; k < 4; k++) {
        if (h == c.H && w == c.W && tmp == c.v) {
          return true;
        }
        tmp = rot(tmp, h);
        swap(h, w);
      }
      tmp = rev(tmp, w);
      for (int k = 0; k < 4; k++) {
        if (h == c.H && w == c.W && tmp == c.v) {
          return true;
        }
        tmp = rot(tmp, h);
        swap(h, w);
      }
      return false;
    } else {
      return false;
    }
  }

  void paint(vector<string>& grid) const
  {
    for (set<pair<int,int> >::const_iterator it = v.begin(); it != v.end(); ++it) {
      grid[i+it->first][j+it->second] = name;
    }
  }
};

cluster find_cluster(vector<string>& grid, int start_i, int start_j)
{
  const int H = grid.size(), W = grid[0].size();
  queue<pair<int,int> > q;
  q.push(make_pair(start_i, start_j));
  grid[start_i][start_j] = MARKED;
  int top = start_i, bottom = start_i, left = start_j, right = start_j;
  set<pair<int,int> > v;
  while (!q.empty()) {
    const pair<int,int> p = q.front();
    q.pop();
    v.insert(p);
    for (int d = 0; d < 8; d++) {
      static const int di[] = {-1, -1, 0, 1, 1, 1, 0, -1};
      static const int dj[] = {0, 1, 1, 1, 0, -1, -1, -1};
      const int i = p.first + di[d];
      const int j = p.second + dj[d];
      if (0 <= i && i < H && 0 <= j && j < W && grid[i][j] == '1') {
        grid[i][j] = MARKED;
        q.push(make_pair(i, j));
        top = min(top, i);
        bottom = max(bottom, i);
        left = min(left, j);
        right = max(right, j);
      }
    }
  }
  cluster c;
  c.i = top;
  c.j = left;
  c.H = bottom - top + 1;
  c.W = right - left + 1;
  for (set<pair<int,int> >::iterator it = v.begin(); it != v.end(); ++it) {
    c.v.insert(make_pair(it->first - c.i, it->second - c.j));
  }
  return c;
}

int main()
{
  ios::sync_with_stdio(false);
  int W, H;
  cin >> W >> H;
  vector<string> grid(H);
  for (int i = 0; i < H; i++) {
    cin >> grid[i];
  }

  char name = 'a';
  vector<cluster> v;
  for (int i = 0; i < H; i++) {
    for (int j = 0; j < W; j++) {
      if (grid[i][j] == '1') {
        cluster c = find_cluster(grid, i, j);
        c.name = name;
        for (vector<cluster>::iterator it = v.begin(); it != v.end(); ++it) {
          if (it->same(c)) {
            c.name = it->name;
            break;
          }
        }
        if (c.name == name) {
          ++name;
          v.push_back(c);
        }
        c.paint(grid);
      }
    }
  }

  copy(grid.begin(), grid.end(), ostream_iterator<string>(cout, "\n"));
  return 0;
}
