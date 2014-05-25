#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

bool augument(const vector<vector<int> >& g, int u, vector<int>& match_to, vector<bool>& visited)/*{{{*/
{
  if (u < 0) {
    return true;
  }

  for (vector<int>::const_iterator it(g[u].begin()); it != g[u].end(); ++it) {
    if (!visited[*it]) {
      visited[*it] = true;
      if (augument(g, match_to[*it], match_to, visited)) {
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
      if (augument(g, u, match_to, visited)) {
        match++;
      }
    }
  }
  return match;
}/*}}}*/

int main()
{
  int N;
  cin >> N;
  while (N-- > 0) {
    int H, W;
    cin >> H >> W;
    vector<string> grid(H);
    for (int i = 0; i < H; i++) {
      cin >> grid[i];
    }

    vector<vector<int> > g(H*W);
    int c = 0;
    for (int i = 0; i < H; i++) {
      for (int j = 0; j < W; j++) {
        if (grid[i][j] == '*') {
          ++c;
          if (j+1 < W && grid[i][j+1] == '*') {
            g[i*W+j].push_back(i*W+j+1);
            g[i*W+j+1].push_back(i*W+j);
          }
          if (i+1 < H && grid[i+1][j] == '*') {
            g[i*W+j].push_back((i+1)*W+j);
            g[(i+1)*W+j].push_back(i*W+j);
          }
        }
      }
    }

    const int m = bipartite_matching(g);
    cout << c-m << endl;
  }
  return 0;
}
