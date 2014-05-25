#include <iostream>
#include <vector>
using namespace std;

struct rect
{
  int c, y1, x1, y2, x2;
  bool above(const rect& r) const
  {
    return y2 == r.y1 && (
        (x1 <= r.x2 && r.x2 <= x2)
        || (x1 <= r.x1 && r.x1 <= x2)
        );
  }
};

int dfs(const vector<rect>& v, const vector<vector<int> >& g, vector<int>& deg, int color, unsigned done)
{
  const int N = v.size();
  if (done == (1<<N)-1) {
    return 0;
  } else {
    int ans = 100;
    for (int i = 0; i < N; i++) {
      if (!(done & (1<<i)) && deg[i] == 0) {

        for (vector<int>::const_iterator it = g[i].begin(); it != g[i].end(); ++it) {
          --deg[*it];
        }
        const int a = dfs(v, g, deg, v[i].c, done | (1<<i));
        ans = min(ans, (color != v[i].c) + a);
        for (vector<int>::const_iterator it = g[i].begin(); it != g[i].end(); ++it) {
          ++deg[*it];
        }
      }
    }
    return ans;
  }
}

int main()
{
  int T;
  cin >> T;
  while (T-- > 0) {
    int N;
    cin >> N;
    vector<rect> v(N);
    vector<int> deg(N, 0);
    vector<vector<int> > g(N);
    for (int i = 0; i < N; i++) {
      cin >> v[i].y1 >> v[i].x1 >> v[i].y2 >> v[i].x2 >> v[i].c;
      for (int j = 0; j < i; j++) {
        if (v[i].above(v[j])) {
          g[i].push_back(j);
          ++deg[j];
        } else if (v[j].above(v[i])) {
          g[j].push_back(i);
          ++deg[i];
        }
      }
    }
    int ans = 100;
    for (int i = 0; i < N; i++) {
      if (deg[i] == 0) {
        for (vector<int>::const_iterator it = g[i].begin(); it != g[i].end(); ++it) {
          --deg[*it];
        }
        ans = min(ans, 1 + dfs(v, g, deg, v[i].c, 1<<i));
        for (vector<int>::const_iterator it = g[i].begin(); it != g[i].end(); ++it) {
          ++deg[*it];
        }
      }
    }
    cout << ans << endl;
  }
  return 0;
}
