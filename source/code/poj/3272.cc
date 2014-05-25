#include <cstdio>
#include <vector>
#include <queue>
using namespace std;

vector<int> bfs(const vector<vector<int> >& g, vector<int>& deg)
{
  const int N = g.size();
  queue<int> q;
  vector<int> v(N, 0);
  for (int i = 0; i < N; i++) {
    if (deg[i] == 0) {
      q.push(i);
      v[i] = 1;
    }
  }
  while (!q.empty()) {
    const int n = q.front();
    q.pop();
    for (vector<int>::const_iterator it(g[n].begin()); it != g[n].end(); ++it) {
      --deg[*it];
      v[*it] += v[n];
      if (deg[*it] == 0) {
        q.push(*it);
      }
    }
  }
  return v;
}

int main()
{
  int N, M;
  scanf("%d %d", &N, &M);
  vector<vector<int> > g(N), g_rev(N);
  vector<int> deg(N, 0), deg_rev(N, 0);
  for (int i = 0; i < M; i++) {
    int u, v;
    scanf("%d %d", &u, &v);
    --u;  --v;
    g[u].push_back(v);
    g_rev[v].push_back(u);
    ++deg[v];
    ++deg_rev[u];
  }

  const vector<int> v = bfs(g, deg);
  const vector<int> v_rev = bfs(g_rev, deg_rev);
  int ans = 0;
  for (int i = 0; i < N; i++) {
    for (vector<int>::const_iterator it(g[i].begin()); it != g[i].end(); ++it) {
      ans = max(ans, v[i] * v_rev[*it]);
    }
  }
  printf("%d\n", ans);
  return 0;
}
