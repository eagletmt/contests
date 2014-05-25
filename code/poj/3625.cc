#include <cstdio>
#include <vector>
#include <algorithm>
#include <complex>
using namespace std;
typedef complex<double> P;

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

struct edge
{
  int u, v;
  double w;
  edge(int a, int b, double c) : u(a), v(b), w(c) {}
  bool operator<(const edge& e) const { return w < e.w; }
};

double kruskal(DisjointSet& s, const vector<edge>& es)
{
  const int N = s.parent.size();
  double ans = 0;
  for (vector<edge>::const_iterator it = es.begin(); s.size(0) < N && it != es.end(); ++it) {
    if (s.unite(it->u, it->v)) {
      ans += it->w;
    }
  }
  return ans;
}

int main()
{
  int N, M;
  scanf("%d %d", &N, &M);
  vector<P> ps;
  for (int i = 0; i < N; i++) {
    int x, y;
    scanf("%d %d", &x, &y);
    ps.push_back(P(x, y));
  }
  DisjointSet s(N);
  for (int i = 0; i < M; i++) {
    int u, v;
    scanf("%d %d", &u, &v);
    --u;  --v;
    s.unite(u, v);
  }

  vector<edge> es;
  for (int i = 0; i < N; i++) {
    for (int j = i+1; j < N; j++) {
      if (!s.find(i, j)) {
        es.push_back(edge(i, j, abs(ps[i] - ps[j])));
      }
    }
  }
  sort(es.begin(), es.end());
  printf("%.2f\n", kruskal(s, es));
  return 0;
}
