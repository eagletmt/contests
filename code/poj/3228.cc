#include <cstdio>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

bool ok(const vector<vector<pair<int,int> > >& g, const vector<int>& gold, int K)
{
  const int N = g.size();
  vector<int> visited(N, false);
  for (int i = 0; i < N; i++) {
    if (visited[i]) {
      continue;
    }
    queue<int> q;
    q.push(i);
    visited[i] = true;
    int c = 0;
    while (!q.empty()) {
      const int n = q.front();
      q.pop();
      c += gold[n];
      for (vector<pair<int,int> >::const_iterator it = g[n].begin(); it != g[n].end(); ++it) {
        const int m = it->first;
        const int d = it->second;
        if (d <= K && !visited[m]) {
          visited[m] = true;
          q.push(m);
        }
      }
    }
    if (c > 0) {
      return false;
    }
  }
  return true;
}

int main()
{
  int N;
  while (scanf("%d", &N) != EOF && N != 0) {
    vector<int> gold(N, 0);
    for (int i = 0; i < N; i++) {
      int c;
      scanf("%d", &c);
      gold[i] += c;
    }
    for (int i = 0; i < N; i++) {
      int c;
      scanf("%d", &c);
      gold[i] -= c;
    }
    vector<vector<pair<int,int> > > g(N);
    int M;
    scanf("%d", &M);
    for (int i = 0; i < M; i++) {
      int u, v, d;
      scanf("%d %d %d", &u, &v, &d);
      --u;  --v;
      g[u].push_back(make_pair(v, d));
      g[v].push_back(make_pair(u, d));
    }

    static const int INF = 1000000;
    int left = 0, right = INF;
    while (left < right) {
      const int mid = (left + right)/2;
      if (ok(g, gold, mid)) {
        right = mid;
      } else {
        left = mid+1;
      }
    }
    if (left == INF) {
      puts("No Solution");
    } else {
      printf("%d\n", left);
    }
  }
  return 0;
}
