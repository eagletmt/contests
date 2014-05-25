#include <cstdio>
#include <vector>
#include <algorithm>
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

struct edge {/*{{{*/
  int u, v;
  int w;
  edge() {}
  bool operator<(const edge& that) const { return w < that.w; }
};/*}}}*/

pair<bool,int> kruskal(const vector<edge>& edges, int N, int M)/*{{{*/
{
  DisjointSet s(N);
  int a = 0;
  for (vector<edge>::const_iterator it = edges.begin(); it != edges.end() && s.size(0) < N; ++it) {
    if (it->w >= M && s.unite(it->u, it->v)) {
      a = max(a, it->w);
    }
  }
  return make_pair(s.size(0) == N, a);
}/*}}}*/

int main()
{
  int N, M;
  while (scanf("%d %d", &N, &M) != EOF && N != 0) {
    vector<edge> es(M);
    for (int i = 0; i < M; i++) {
      scanf("%d %d %d", &es[i].u, &es[i].v, &es[i].w);
      --es[i].u;  --es[i].v;
    }
    sort(es.begin(), es.end());
    static const int INF = 10000000;
    int ans = INF;
    for (int i = 0; i < M; i++) {
      const pair<bool,int> r = kruskal(es, N, es[i].w);
      if (r.first) {
        ans = min(ans, r.second - es[i].w);
      }
    }
    if (ans == INF) {
      puts("-1");
    } else {
      printf("%d\n", ans);
    }
  }
  return 0;
}
