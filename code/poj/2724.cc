#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

bool bm_augment(const vector<vector<int> >& g, int u, vector<int>& match_to, vector<bool>& visited)/*{{{*/
{
  if (u < 0) {
    return true;
  }

  for (vector<int>::const_iterator it(g[u].begin()); it != g[u].end(); ++it) {
    if (!visited[*it]) {
      visited[*it] = true;
      if (bm_augment(g, match_to[*it], match_to, visited)) {
        match_to[*it] = u;
        return true;
      }
    }
  }
  return false;
}/*}}}*/

void coloring(const vector<vector<int> >& g, int u, vector<int>& color)/*{{{*/
{
  for (vector<int>::const_iterator it = g[u].begin(); it != g[u].end(); ++it) {
    if (color[*it] == 0) {
      color[*it] = -color[u];
      coloring(g, *it, color);
    }
  }
}/*}}}*/

int bipartite_matching(const vector<vector<int> >& g)/*{{{*/
{
  const int N = g.size();
  vector<int> color(N, 0);
  for (int u = 0; u < N; u++) {
    if (color[u] == 0) {
      color[u] = 1;
      coloring(g, u, color);
    }
  }
  vector<int> match_to(N, -1);
  int match = 0;
  vector<bool> visited(N);
  for (int u = 0; u < N; u++) {
    if (color[u] == 1) {
      fill(visited.begin(), visited.end(), false);
      if (bm_augment(g, u, match_to, visited)) {
        match++;
      }
    }
  }
  return match;
}/*}}}*/

int main()
{
  int N, M;
  while (cin >> N >> M && N != 0) {
    vector<int> v;
    for (int i = 0; i < M; i++) {
      string s;
      cin >> s;
      if (s.find('*') != string::npos) {
        int n = 0, m = 0;
        for (string::const_iterator it = s.begin(); it != s.end(); ++it) {
          if (*it == '*') {
            n = 2*n + 0;
            m = 2*m + 1;
          } else {
            n = 2*n + (*it-'0');
            m = 2*m + (*it-'0');
          }
        }
        v.push_back(n);
        v.push_back(m);
      } else {
        int n = 0;
        for (string::const_iterator it = s.begin(); it != s.end(); ++it) {
          n = 2*n + (*it-'0');
        }
        v.push_back(n);
      }
    }
    sort(v.begin(), v.end());
    v.erase(unique(v.begin(), v.end()), v.end());

    vector<vector<int> > g(1<<N);
    for (vector<int>::const_iterator it = v.begin(); it != v.end(); ++it) {
      for (vector<int>::const_iterator jt = it+1; jt != v.end(); ++jt) {
        if (__builtin_popcount(*it ^ *jt) == 1) {
          g[*it].push_back(*jt);
          g[*jt].push_back(*it);
        }
      }
    }

    cout << v.size()-bipartite_matching(g) << endl;
  }
  return 0;
}
