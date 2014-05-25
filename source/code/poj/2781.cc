#include <cstdio>
#include <vector>
#include <queue>
using namespace std;

int bfs(const vector<vector<int> >& g, int start, int goal)
{
  queue<pair<int,int> > q;
  q.push(make_pair(start, 0));
  vector<bool> visited(g.size(), false);
  visited[start] = true;
  while (!q.empty()) {
    const pair<int,int> p = q.front();
    q.pop();
    const int n = p.first;
    const int d = p.second;
    if (n == goal) {
      return d-1;
    }
    for (vector<int>::const_iterator it(g[n].begin()); it != g[n].end(); ++it) {
      if (!visited[*it]) {
        visited[*it] = true;
        q.push(make_pair(*it, d+1));
      }
    }
  }
  return -1;
}

int main()
{
  int N;
  scanf("%d", &N);
  vector<vector<int> > g(N);
  for (int i = 0; i < N; i++) {
    int c, nc;
    scanf("%d %d", &c, &nc);
    g[c].resize(nc);
    for (int j = 0; j < nc; j++) {
      scanf("%d", &g[c][j]);
    }
  }
  int c1, c2;
  scanf("%d %d", &c1, &c2);

  printf("%d %d %d\n", c1, c2, bfs(g, c1, c2));
  return 0;
}
