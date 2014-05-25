#include <cstdio>
#include <vector>
using namespace std;

struct DisjointSet/*{{{*/
{
  vector<int> parent;

  int root(int x)
  {
    if (parent[x] < 0) {
      return x;
    } else {
      parent[x] = root(parent[x]);
      return parent[x];
    }
  }

  explicit DisjointSet(int n) : parent(n, -1) {}

  bool unite(int x, int y)
  {
    const int a = root(x);
    const int b = root(y);
    if (a != b) {
      if (parent[a] < parent[b]) {
        parent[a] += parent[b];
        parent[b] = a;
      } else {
        parent[b] += parent[a];
        parent[a] = b;
      }
      return true;
    } else {
      return false;
    }
  }

  bool find(int x, int y) { return root(x) == root(y); }
  int size(int x) { return -parent[root(x)]; }
};/*}}}*/

int main()
{
  int N, D;
  scanf("%d %d", &N, &D);
  vector<pair<int,int> > v(N);
  for (int i = 0; i < N; i++) {
    scanf("%d %d", &v[i].first, &v[i].second);
  }

  vector<vector<int> > g(N, vector<int>(N, false));
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < N; j++) {
      const int x = v[i].first - v[j].first;
      const int y = v[i].second - v[j].second;
      g[i][j] = x*x + y*y <= D*D;
    }
  }

  vector<int> repaired(N, false);
  char cmd[8];
  int p;
  DisjointSet s(N);
  while (scanf("%s %d", cmd, &p) != EOF) {
    --p;
    if (*cmd == 'S') {
      int q;
      scanf("%d", &q);
      --q;
      puts(s.find(p, q) ? "SUCCESS" : "FAIL");
    } else {
      if (!repaired[p]) {
        repaired[p] = true;
        for (int i = 0; i < N; i++) {
          if (g[p][i] && repaired[i]) {
            s.unite(p, i);
          }
        }
      }
    }
  }
  return 0;
}
