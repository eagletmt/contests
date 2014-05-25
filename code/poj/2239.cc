#include <cstdio>
#include <vector>
using namespace std;

bool augument(const vector<vector<int> >& g, int u, vector<int>& match_to, vector<bool>& visited) // {{{
{
  if (u < 0) {
    return true;
  }

  for (vector<int>::const_iterator it(g[u].begin()); it != g[u].end(); ++it) {
    if (!visited[*it]) {
      visited[*it] = true;
      if (augument(g, match_to[*it], match_to, visited)) {
        match_to[u] = *it;
        match_to[*it] = u;
        return true;
      }
    }
  }
  return false;
} // }}}

int bipartite_matching(const vector<vector<int> >& g) // {{{
{
  const int N = g.size();
  vector<int> match_to(N, -1);
  int match = 0;
  for (int u = 0; u < N; u++) {
    vector<bool> visited(N, false);
    if (augument(g, u, match_to, visited)) {
      match++;
    }
  }
  return match;
} // }}}

int main()
{
  int N;
  while (scanf("%d", &N) != EOF) {
    vector<vector<int> > g(N + 7*12);
    for (int i = 0; i < N; i++) {
      int m;
      scanf("%d", &m);
      for (int j = 0; j < m; j++) {
        int p, q;
        scanf("%d %d", &p, &q);
        --p;  --q;
        g[i].push_back(N + 12*p+q);
      }
    }
    printf("%d\n", bipartite_matching(g));
  }
  return 0;
}
