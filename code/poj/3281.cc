#include <cstdio>
#include <vector>
#include <queue>
using namespace std;
static const int INF = 10000000;

template <typename T>
T edmonds_karp(const vector<vector<T> >& capacity, int source, int sink)/*{{{*/
{
  const int N = capacity.size();
  vector<vector<T> > flow(N, vector<T>(N, 0));
  T max_flow = 0;

  while (true) {
    vector<int> parent(N, -1);
    queue<int> q;
    q.push(source);

    while (!q.empty() && parent[sink] < 0) {
      const int v = q.front();
      q.pop();

      for (int u = 0; u < N; u++) {
        if (parent[u] < 0 && capacity[v][u] - flow[v][u] > 0) {
          parent[u] = v;
          if (u == sink) {
            break;
          }
          q.push(u);
        }
      }
    }

    if (parent[sink] < 0) {
      break;
    }

    T aug = INF;
    for (int v = sink; v != source; v = parent[v]) {
      const int u = parent[v];
      aug = min(aug, capacity[u][v] - flow[u][v]);
    }
    max_flow += aug;
    for (int v = sink; v != source; v = parent[v]) {
      const int u = parent[v];
      flow[u][v] += aug;
      flow[v][u] -= aug;
    }
  }

  return max_flow;
}/*}}}*/

int main()
{
  int N, F, D;
  scanf("%d %d %d", &N, &F, &D);
  const int M = F + N + N + D + 2;
  const int source = M-2, sink = M-1;
  vector<vector<int> > c(M, vector<int>(M, 0));
  for (int i = 0; i < F; i++) {
    c[source][i] = 1;
  }
  for (int i = 0; i < N; i++) {
    c[F+i][F+N+i] = 1;
  }
  for (int i = 0; i < D; i++) {
    c[F+N+N+i][sink] = 1;
  }

  for (int i = 0; i < N; i++) {
    int n, m;
    scanf("%d %d", &n, &m);
    for (int j = 0; j < n; j++) {
      int f;
      scanf("%d", &f);
      --f;
      c[f][F+i] = 1;
    }
    for (int j = 0; j < m; j++) {
      int d;
      scanf("%d", &d);
      --d;
      c[F+N+i][F+N+N+d] = 1;
    }
  }

  printf("%d\n", edmonds_karp(c, source, sink));
  return 0;
}
