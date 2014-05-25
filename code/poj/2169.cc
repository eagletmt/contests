#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

int main()
{
  ios::sync_with_stdio(false);
  int N, M, a1, b1, a2, b2;
  cin >> N >> M >> a1 >> b1 >> a2 >> b2;
  --a1; --b1; --a2; --b2;
  vector<vector<int> > g(N), c(N, vector<int>(N, false));
  for (int i = 0; i < M; i++) {
    int u, v;
    cin >> u >> v;
    --u;  --v;
    g[u].push_back(v);
    g[v].push_back(u);
    c[u][v] = c[v][u] = true;
  }
  static int dist[100][100];
  static const int INF = 10000000;
  for (int i = 0; i < N; i++) {
    fill_n(dist[i], N, INF);
  }
  dist[a1][b1] = 0;
  static pair<int,int> prev[100][100];
  queue<pair<int,int> > q;
  q.push(make_pair(a1, b1));
  prev[a1][b1] = make_pair(-1, -1);
  while (!q.empty()) {
    const int a = q.front().first;
    const int b = q.front().second;
    q.pop();
    if (a == a2 && b == b2) {
      break;
    }
    const int d = dist[a][b];
    for (vector<int>::const_iterator it = g[a].begin(); it != g[a].end(); ++it) {
      if (c[*it][b] && d+1 < dist[*it][b]) {
        dist[*it][b] = d+1;
        prev[*it][b] = make_pair(a, b);
        q.push(make_pair(*it, b));
      }
    }
    for (vector<int>::const_iterator it = g[b].begin(); it != g[b].end(); ++it) {
      if (c[a][*it] && d+1 < dist[a][*it]) {
        dist[a][*it] = d+1;
        prev[a][*it] = make_pair(a, b);
        q.push(make_pair(a, *it));
      }
    }
    for (vector<int>::const_iterator it = g[a].begin(); it != g[a].end(); ++it) {
      for (vector<int>::const_iterator jt = g[b].begin(); jt != g[b].end(); ++jt) {
        if (!(*it == b && *jt == a) && c[*it][*jt] && d+2 < dist[*it][*jt]) {
          dist[*it][*jt] = d+2;
          prev[*it][*jt] = make_pair(a, b);
          q.push(make_pair(*it, *jt));
        }
      }
    }
  }

  vector<pair<int,int> > ans;
  for (int a = a2, b = b2; a >= 0;) {
    ans.push_back(make_pair(a, b));
    const pair<int,int> p = prev[a][b];
    a = p.first;
    b = p.second;
  }
  cout << dist[a2][b2] << ' ' << ans.size() << endl;
  for (vector<pair<int,int> >::const_reverse_iterator it = ans.rbegin(); it != ans.rend(); ++it) {
    cout << it->first+1 << ' ' << it->second+1 << endl;
  }
  return 0;
}
