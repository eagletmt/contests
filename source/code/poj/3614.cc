#include <cstdio>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;
static const int MAXN = 2500 + 2500 + 2;
static const int INF = 10000000;

template <class Flow>
struct edge
{
  int id;
  Flow capacity, flow;
  int back;
  edge(int i, Flow c, int b) : id(i), capacity(c), flow(0), back(b) {}
};

template <class Flow>
void make_edge(vector<edge<Flow> > *g, int src, int dst, Flow c)
{
  const int i = g[src].size(), j = g[dst].size();
  g[src].push_back(edge<Flow>(dst, c, j));
  g[dst].push_back(edge<Flow>(src, 0, i));
}

template <class Flow>
Flow dinic_augment(vector<edge<Flow> > *g, int N, int *level, bool *finished, int u, int sink, int cur)/*{{{*/
{
  if (u == sink || cur == 0) {
    return cur;
  }
  if (finished[u]) {
    return 0;
  }
  finished[u] = true;
  for (typename vector<edge<Flow> >::iterator it = g[u].begin(); it != g[u].end(); ++it) {
    const int v = it->id;
    if (it->capacity - it->flow > 0 && level[v] > level[u]) {
      const int f = dinic_augment(g, N, level, finished, v, sink, min(cur, it->capacity - it->flow));
      if (f > 0) {
        it->flow += f;
        g[v][it->back].flow -= f;
        finished[u] = false;
        return f;
      }
    }
  }
  return 0;
}/*}}}*/
template <class Flow>
Flow dinic(vector<edge<Flow> > *g, int N, int source, int sink)/*{{{*/
{
  Flow max_flow = 0;

  while (true) {
    static int level[MAXN];
    fill_n(level, N, -1);
    level[source] = 0;
    queue<int> q;
    q.push(source);

    int d = N;
    while (!q.empty() && level[q.front()] < d) {
      const int u = q.front();
      q.pop();

      if (u == sink) {
        d = level[u];
      }
      for (typename vector<edge<Flow> >::iterator it = g[u].begin(); it != g[u].end(); ++it) {
        const int v = it->id;
        if (level[v] < 0 && it->capacity - it->flow > 0) {
          q.push(v);
          level[v] = level[u] + 1;
        }
      }
    }

    static bool finished[MAXN];
    fill_n(finished, N, false);
    bool updated = false;
    while (true) {
      const int f = dinic_augment(g, N, level, finished, source, sink, INF);
      if (f == 0) {
        break;
      }
      max_flow += f;
      updated = true;
    }

    if (!updated) {
      break;
    }
  }

  return max_flow;
}/*}}}*/

int main()
{
  int C, L;
  scanf("%d %d", &C, &L);
  static pair<int,int> cows[2500];
  static vector<edge<int> > g[MAXN];
  const int source = C+L, sink = source+1;
  for (int i = 0; i < C; i++) {
    scanf("%d %d", &cows[i].first, &cows[i].second);
    make_edge(g, i, sink, 1);
  }
  for (int j = 0; j < L; j++) {
    int s, p;
    scanf("%d %d", &s, &p);
    make_edge(g, source, C+j, p);
    for (int i = 0; i < C; i++) {
      if (cows[i].first <= s && s <= cows[i].second) {
        make_edge(g, C+j, i, 1);
      }
    }
  }
  printf("%d\n", dinic(g, C+L+2, source, sink));
  return 0;
}
