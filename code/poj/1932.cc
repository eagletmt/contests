#include <cstdio>
#include <vector>
#include <queue>
using namespace std;

struct edge {
  int u, v;
  typedef int weight_type;
  weight_type w;
  edge(int s, int d, weight_type w_) : u(s), v(d), w(w_) {}
};

template <typename Edge>
pair<vector<typename Edge::weight_type>, bool>
bellman_ford(const vector<Edge>& g,/*{{{*/
    typename vector<Edge>::size_type N,
    typename vector<Edge>::size_type start,
    typename Edge::weight_type inf = 10000000)
{
  /* Edge must have
   * - u (source node)
   * - v (dest node)
   * - w (weight)
   * - weight_type
   */
  typedef typename vector<Edge>::size_type size_type;
  typedef typename Edge::weight_type weight_type;
  vector<weight_type> dist(N, inf);
  dist[start] = 0;

  for (size_type i = 0; i < N; i++) {
    for (typename vector<Edge>::const_iterator it = g.begin(); it != g.end(); ++it) {
      const weight_type w = dist[it->u] + it->w;
      if (w < 100 && w < dist[it->v]) {
        dist[it->v] = w;
      }
    }
  }

  for (typename vector<Edge>::const_iterator it = g.begin(); it != g.end(); ++it) {
      const weight_type w = dist[it->u] + it->w;
    if (w < 100 && w < dist[it->v]) {
      return make_pair(dist, false);
    }
  }
  return make_pair(dist, true);
}/*}}}*/

void dfs(const vector<vector<int> >& g, int u, vector<int>& reachable)
{
  if (reachable[u]) {
    return;
  }
  reachable[u] = true;
  for (vector<int>::const_iterator it = g[u].begin(); it != g[u].end(); ++it) {
    dfs(g, *it, reachable);
  }
}

int main()
{
  int N;
  while (scanf("%d", &N) != EOF && N != -1) {
    vector<int> energy(N);
    vector<vector<int> > g(N);
    for (int i = 0; i < N; i++) {
      scanf("%d", &energy[i]);
      energy[i] = -energy[i];
      int m;
      scanf("%d", &m);
      for (int j = 0; j < m; j++) {
        int u;
        scanf("%d", &u);
        --u;
        // rev
        g[u].push_back(i);
      }
    }

    vector<int> reachable(N, false);
    dfs(g, N-1, reachable);
    vector<edge> edges;
    for (int i = 0; i < N; i++) {
      if (!reachable[i]) {
        continue;
      }
      for (vector<int>::const_iterator it = g[i].begin(); it != g[i].end(); ++it) {
        if (!reachable[*it]) {
          continue;
        }
        edges.push_back(edge(*it, i, energy[i]));
      }
    }

    const pair<vector<int>, bool> r = bellman_ford(edges, N, 0);
    if (!r.second || r.first[N-1] < 100) {
      puts("winnable");
    } else {
      puts("hopeless");
    }
  }
  return 0;
}
