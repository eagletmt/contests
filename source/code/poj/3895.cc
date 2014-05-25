#include <iostream>
#include <vector>
using namespace std;

int ans;
void dfs(const vector<vector<int> >& g, int u, int prev, int depth, vector<int>& visited)
{
  if (visited[u] == -1) {
    visited[u] = depth;
    for (vector<int>::const_iterator it = g[u].begin(); it != g[u].end(); ++it) {
      if (*it != prev) {
        dfs(g, *it, u, depth+1, visited);
      }
    }
  } else {
    ans = max(ans, depth - visited[u]);
  }
}

int main()
{
  ios::sync_with_stdio(false);
  int T;
  cin >> T;
  while (T-- > 0) {
    int N, M;
    cin >> N >> M;
    vector<vector<int> > g(N);
    for (int i = 0; i < M; i++) {
      int u, v;
      cin >> u >> v;
      --u;  --v;
      g[u].push_back(v);
      g[v].push_back(u);
    }

    ans = 0;
    vector<int> visited(N, -1);
    dfs(g, 0, -1, 0, visited);
    cout << ans << endl;
  }
  return 0;
}
