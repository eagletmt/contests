#include <cstdio>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;
static const int INF = 1000000000;
static const int MAXN = 100000;
static const int MAXM = 200000;
static const int SECTION_SIZE = 450;

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
  int u, v, c;
  bool operator<(const edge& e) const { return c > e.c; }
};

void lca_dfs(const vector<int> *tree, const int *parent, int *P, int *L, int depth, int n)
{
  L[n] = depth;
  if (depth < SECTION_SIZE) {
    P[n] = 1;
  } else {
    if (!(depth % SECTION_SIZE)) {
      P[n] = parent[n];
    } else {
      P[n] = P[parent[n]];
    }
  }
  for (vector<int>::const_iterator it = tree[n].begin(); it != tree[n].end(); ++it) {
    lca_dfs(tree, parent, P, L, depth+1, *it);
  }
}

int lca_query(const int *parent, const int *P, const int *L, int u, int v)
{
  while (P[u] != P[v]) {
    if (L[u] > L[v]) {
      u = P[u];
    } else {
      v = P[v];
    }
  }
  while (u != v) {
    if (L[u] > L[v]) {
      u = parent[u];
    } else {
      v = parent[v];
    }
  }
  return u;
}

int main()
{
  int N, M, K, Q;
  scanf("%d %d %d %d", &N, &M, &K, &Q);
  vector<vector<pair<int,int> > > g(N);
  static edge edges[MAXM];
  for (int i = 0; i < M; i++) {
    edge& e = edges[i];
    scanf("%d %d %d", &e.u, &e.v, &e.c);
    --e.u;  --e.v;
    g[e.u].push_back(make_pair(e.v, e.c));
    g[e.v].push_back(make_pair(e.u, e.c));
  }

  static int dist[2*MAXN];
  fill_n(dist, N, INF);
  priority_queue<pair<int,int> > q;
  for (int i = 0; i < K; i++) {
    int F;
    scanf("%d", &F);
    --F;
    dist[F] = 0;
    q.push(make_pair(0, F));
  }

  while (!q.empty()) {
    const int c = -q.top().first;
    const int n = q.top().second;
    q.pop();
    if (dist[n] < c) {
      continue;
    }
    for (vector<pair<int,int> >::const_iterator it = g[n].begin(); it != g[n].end(); ++it) {
      const int m = it->first;
      const int cc = c + it->second;
      if (cc < dist[m]) {
        dist[m] = cc;
        q.push(make_pair(-cc, m));
      }
    }
  }

  for (int i = 0; i < M; i++) {
    edge& e = edges[i];
    e.c = min(dist[e.u], dist[e.v]);
  }
  sort(edges, edges+M);
  DisjointSet s(N);
  static int m[MAXN];
  for (int i = 0; i < N; i++) {
    m[i] = i;
  }
  static int parent[2*MAXN];
  static vector<int> tree[2*MAXN];
  int uniq = N;
  for (int i = 0; i < M; i++) {
    const edge& e = edges[i];
    const int x = s.root(e.u);
    const int y = s.root(e.v);
    if (s.unite(x, y)) {
      parent[m[x]] = parent[m[y]] = uniq;
      dist[uniq] = min(dist[m[x]], dist[m[y]]);
      tree[uniq].push_back(m[x]);
      tree[uniq].push_back(m[y]);
      m[s.root(x)] = uniq;
      ++uniq;
    }
  }

  static int P[2*MAXN], L[2*MAXN];
  lca_dfs(tree, parent, P, L, 0, uniq-1);

  for (int i = 0; i < Q; i++) {
    int S, T;
    scanf("%d %d", &S, &T);
    --S;  --T;
    const int u = lca_query(parent, P, L, S, T);
    printf("%d\n", dist[u]);
  }

  return 0;
}
