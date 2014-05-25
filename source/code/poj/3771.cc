#include <cstdio>
#include <vector>
#include <algorithm>
#include <complex>
using namespace std;
typedef complex<double> P;

struct edge
{
  int u, v;
  double d;
  edge(int a, int b, double c) : u(a), v(b), d(c) {}
  bool operator<(const edge& e) const { return d < e.d; }
};

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

double kruskal(const vector<edge>& g, int N, int bill)
{
  double c = 0;
  DisjointSet s(N);
  for (vector<edge>::const_iterator it = g.begin(); it != g.end(); ++it) {
    if (it->u == bill || it->v == bill) {
      continue;
    }
    if (s.unite(it->u, it->v)) {
      c += it->d;
    }
  }
  return c;
}

int main()
{
  int T;
  scanf("%d", &T);
  while (T-- > 0) {
    int N;
    scanf("%d", &N);
    vector<P> v;
    for (int i = 0; i < N; i++) {
      int x, y;
      scanf("%d %d", &x, &y);
      v.push_back(P(x, y));
    }

    vector<edge> g;
    for (int i = 0; i < N; i++) {
      for (int j = i+1; j < N; j++) {
        g.push_back(edge(i, j, abs(v[i] - v[j])));
      }
    }
    sort(g.begin(), g.end());

    double ans = 1e10;
    for (int i = 0; i < N; i++) {
      ans = min(ans, kruskal(g, N, i));
    }
    printf("%.2f\n", ans);
  }
  return 0;
}
