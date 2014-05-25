#include <cstdio>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

struct edge { int u, v, c; };

int main()
{
  int N;
  while (scanf("%d", &N) != EOF && N != 0) {
    int M;
    scanf("%d", &M);
    static vector<pair<int,int> > g[600];
    for (int i = 0; i < N; i++) {
      g[i].clear();
    }

    static edge es[10000];
    for (int i = 0; i < M; i++) {
      scanf("%d %d %d", &es[i].u, &es[i].v, &es[i].c);
      --es[i].v;  --es[i].u;
    }
    static int color[600];
    for (int i = 0; i < N; i++) {
      scanf("%d", &color[i]);
    }
    for (int i = 0; i < M; i++) {
      if (color[es[i].u] <= color[es[i].v]) {
        g[es[i].u].push_back(make_pair(es[i].v, es[i].c));
      }
      if (color[es[i].v] <= color[es[i].u]) {
        g[es[i].v].push_back(make_pair(es[i].u, es[i].c));
      }
    }

    static int dist[600];
    static const int INF = 10000000;
    fill_n(dist, N, INF);
    priority_queue<pair<int,int> > q;
    q.push(make_pair(0, 0));
    dist[0] = 0;
    while (!q.empty()) {
      const int c = -q.top().first;
      const int n = q.top().second;
      q.pop();
      if (n == 1) {
        break;
      }
      if (dist[n] < c) {
        continue;
      }
      for (vector<pair<int,int> >::const_iterator it = g[n].begin(); it != g[n].end(); ++it) {
        const int m = it->first;
        const int cc = c + it->second;
        if (cc < dist[m]) {
          dist[m] = cc;
          q.push(make_pair(-cc, m));
        }
      }
    }
    if (dist[1] == INF) {
      puts("-1");
    } else {
      printf("%d\n", dist[1]);
    }
  }
  return 0;
}
