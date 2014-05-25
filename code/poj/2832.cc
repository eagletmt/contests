#include <cstdio>
#include <algorithm>
using namespace std;
static const int MAXN = 10000, MAXM = 50000;

struct DisjointSet/*{{{*/
{
  int parent[MAXN];

  int root(int x)
  {
    if (parent[x] < 0) {
      return x;
    } else {
      parent[x] = root(parent[x]);
      return parent[x];
    }
  }

  explicit DisjointSet(int n)
  {
    fill_n(parent, n, -1);
  }

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
  int u, v, c;
  bool operator<(const edge& e) const { return c < e.c; }
};

int main()
{
  int N, M, Q;
  scanf("%d %d %d", &N, &M, &Q);
  static edge es[MAXM];
  for (int i = 0; i < M; i++) {
    scanf("%d %d %d", &es[i].u, &es[i].v, &es[i].c);
    --es[i].u; --es[i].v;
  }
  sort(es, es+M);

  static DisjointSet s(N);
  static int cs[MAXM+2], as[MAXM+2];
  int acc = 0;
  for (int i = 0; i < M; i++) {
    const int c = es[i].c;
    const int u = s.root(es[i].u);
    const int v = s.root(es[i].v);
    if (u != v) {
      acc += s.size(u) * s.size(v);
      s.unite(u, v);
    }
    cs[i+1] = c;
    as[i+1] = acc;
  }
  static const int INF = 100000000;
  cs[M+1] = INF;
  as[M+1] = acc;

  while (Q-- > 0) {
    int A;
    scanf("%d", &A);
    const int idx = upper_bound(cs, cs+M+2, A) - cs - 1;
    printf("%d\n", as[idx]);
  }
  return 0;
}
