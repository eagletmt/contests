#include <cstdio>
#include <vector>
#include <queue>
using namespace std;
static const int Y = 365;
static const int MAXN = 2*Y+2;

template <class Flow, class Cost>
struct edge
{
  int index;
  Flow capacity, flow;
  Cost cost;
  int back;
  edge(int i, Flow c, Cost d, int b) : index(i), capacity(c), flow(0), cost(d), back(b) {}
};

template <class Flow, class Cost>
void make_edge(vector<edge<Flow, Cost> > *g, int src, int dst, Flow c, Cost d)
{
  const int i = g[src].size(), j = g[dst].size();
  g[src].push_back(edge<Flow, Cost>(dst, c, d, j));
  g[dst].push_back(edge<Flow, Cost>(src, 0, -d, i));
}

template <class Flow, class Cost>
pair<Flow, Cost>
primal_dual(vector<edge<Flow, Cost> > *g, int N, int source, int sink, int max_flow)/*{{{*/
{
  pair<Flow, Cost> total;
  static Cost h[MAXN], dist[MAXN];
  static pair<int,int> parent[MAXN];
  for (Flow f = max_flow; f > 0; ) {
    fill_n(dist, N, 1000000);
    dist[source] = 0;
    fill_n(parent, N, make_pair(-1, -1));
    priority_queue<pair<Cost,int> > q;
    q.push(make_pair(0, source));
    while (!q.empty()) {
      const int n = q.top().second;
      const Cost c = -q.top().first;
      q.pop();
      if (dist[n] < c) {
        continue;
      }
      for (typename vector<edge<Flow, Cost> >::const_iterator it = g[n].begin(); it != g[n].end(); ++it) {
        if (it->capacity - it->flow > 0) {
          const Cost c2 = c + it->cost + h[n] - h[it->index];
          if (c2 < dist[it->index]) {
            dist[it->index] = c2;
            parent[it->index] = make_pair(n, it - g[n].begin());
            q.push(make_pair(-c2, it->index));
          }
        }
      }
    }
    if (parent[sink].first == -1) {
      break;
    }

    Flow e = f;
    for (int i = sink; i != source; i = parent[i].first) {
      const edge<Flow, Cost>& x = g[parent[i].first][parent[i].second];
      e = min(e, x.capacity - x.flow);
    }
    for (int i = sink; i != source; i = parent[i].first) {
      edge<Flow, Cost>& x = g[parent[i].first][parent[i].second];
      total.second += e * x.cost;
      x.flow += e;
      g[x.index][x.back].flow -= e;
    }
    f -= e;
    total.first += e;
    for (int i = 0; i < N; i++) {
      h[i] += dist[i];
    }
  }

  return total;
}/*}}}*/

int main()
{
  int N;
  while (scanf("%d", &N) == 1 && N != 0) {
    static vector<edge<int,int> > g[MAXN];
    for (int i = 0; i < MAXN; i++) {
      g[i].clear();
    }
    for (int i = 0; i < N; i++) {
      int u, v, w;
      scanf("%d %d %d", &u, &v, &w);
      make_edge(g, 2*u-1, 2*v, 1, -w);
    }
    for (int i = 0; i < MAXN-1; i++) {
      make_edge(g, i, i+1, 2, 0);
    }

    printf("%d\n", -primal_dual(g, MAXN, 0, MAXN-1, 2).second);
  }
  return 0;
}
