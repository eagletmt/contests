#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;

bool bm_augment(const vector<vector<int> >& g, int u, vector<int>& match_to, vector<int>& visited) // {{{
{
  if (u < 0) {
    return true;
  }

  for (vector<int>::const_iterator it(g[u].begin()); it != g[u].end(); ++it) {
    if (!visited[*it]) {
      visited[*it] = true;
      if (bm_augment(g, match_to[*it], match_to, visited)) {
        match_to[u] = *it;
        match_to[*it] = u;
        return true;
      }
    }
  }
  return false;
} // }}}

int bipartite_matching(const vector<vector<int> >& g)  // {{{
{
  const int N = g.size();
  vector<int> match_to(N, -1);
  int match = 0;
  for (int u = 0; u < N; u++) {
    vector<int> visited(N, false);
    if (bm_augment(g, u, match_to, visited)) {
      match++;
    }
  }
  return match;
} // }}}

int main()
{
  int N, M, L;
  while (scanf("%d %d %d", &N, &M, &L) != EOF && N != 0) {
    static const int INF = 10000000;
    vector<vector<int> > dist(N, vector<int>(N, INF));
    for (int i = 0; i < N; i++) {
      dist[i][i] = 0;
    }
    for (int i = 0; i < M; i++) {
      int u, v, d;
      scanf("%d %d %d", &u, &v, &d);
      dist[u][v] = min(dist[u][v], d);
      dist[v][u] = min(dist[v][u], d);
    }
    vector<pair<int,int> > pt(L);
    for (int i = 0; i < L; i++) {
      scanf("%d %d", &pt[i].first, &pt[i].second);
    }

    for (int k = 0; k < N; k++) {
      for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
          dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
        }
      }
    }

    vector<vector<int> > g(2*L);
    for (int i = 0; i < L; i++) {
      for (int j = 0; j < L; j++) {
        if (i == j) {
          continue;
        }
        const int u = pt[i].first;
        const int v = pt[j].first;
        if (dist[u][v] <= pt[j].second - pt[i].second) {
          g[i].push_back(j+L);
        }
      }
    }
    const int r = bipartite_matching(g);
    printf("%d\n", L-r);
  }
  return 0;
}
