#include <iostream>
#include <vector>
using namespace std;

bool bm_augment(const vector<vector<int> >& g, int u, vector<int>& match_to, vector<bool>& visited) // {{{
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

// O(V(V+E))
int bipartite_matching(const vector<vector<int> >& g)  // {{{
{
  const int N = g.size();
  vector<int> match_to(N, -1);
  int match = 0;
  for (int u = 0; u < N; u++) {
    vector<bool> visited(N, false);
    if (bm_augment(g, u, match_to, visited)) {
      match++;
    }
  }
  return match;
} // }}}

int main()
{
  int R, C;
  cin >> R >> C;
  vector<string> grid(R);
  for (int i = 0; i < R; i++) {
    cin >> grid[i];
  }

  const int N = R*C;
  vector<vector<int> > g(2*N);
  for (int i = 0; i < R; i++) {
    for (int j = 0; j < C; j++) {
      if (grid[i][j] == '*') {
        int k = i;
        while (k > 0 && grid[k-1][j] == '*') {
          --k;
        }
        int l = j;
        while (l > 0 && grid[i][l-1] == '*') {
          --l;
        }
        g[k*C+j].push_back(N + i*C+l);
      }
    }
  }

  cout << bipartite_matching(g) << endl;
  return 0;
}
