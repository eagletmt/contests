#include <cstdio>
#include <queue>
#include <algorithm>
using namespace std;
static const int M = 210;
static const int INF = 1000000;

template <class T>
T augment(const T capacity[M][M], int N, T flow[M][M], int level[M], bool finished[M], int u, int sink, T cur)
{
  if (u == sink || cur == 0) {
    return cur;
  }
  if (finished[u]) {
    return 0;
  }
  finished[u] = true;
  for (int v = 0; v < N; v++) {
    if (capacity[u][v] - flow[u][v] > 0 && level[v] > level[u]) {
      const T f = augment(capacity, N, flow, level, finished, v, sink, min(cur, capacity[u][v] - flow[u][v]));
      if (f > 0) {
        flow[u][v] += f;
        flow[v][u] -= f;
        finished[u] = false;
        return f;
      }
    }
  }
  return 0;
}

template <typename T>
T dinic(const T capacity[M][M], int N, int source, int sink)/*{{{*/
{
  static T flow[M][M];
  for (int i = 0; i < N; i++) {
    fill_n(flow[i], N, 0);
  }
  T max_flow = 0;

  while (true) {
    static int level[M];
    fill_n(level, N, -1);
    level[source] = 0;
    queue<int> q;
    q.push(source);

    int d = N;
    while (!q.empty() && level[q.front()] < d) {
      const int u = q.front();
      q.pop();

      if (u == sink) {
        d = level[u];
      }
      for (int v = 0; v < N; v++) {
        if (level[v] < 0 && capacity[u][v] - flow[u][v] > 0) {
          q.push(v);
          level[v] = level[u] + 1;
        }
      }
    }

    static bool finished[M];
    fill_n(finished, M, false);
    bool updated = false;
    while (true) {
      const T f = augment(capacity, N, flow, level, finished, source, sink, INF);
      if (f == 0) {
        break;
      }
      max_flow += f;
      updated = true;
    }

    if (!updated) {
      break;
    }
  }

  return max_flow;
}/*}}}*/

inline double dd(const pair<int,int>& a, const pair<int,int>& b)
{
  const int x = a.first - b.first;
  const int y = a.second - b.second;
  return x*x + y*y;
}

int main()
{
  int T;
  scanf("%d", &T);
  while (T-- > 0) {
    int N;
    double D;
    scanf("%d %lf", &N, &D);
    const int source = 2*N;
    const int sink = source + 1;
    static int capacity[M][M];
    for (int i = 0; i < 2*N+2; i++) {
      fill_n(capacity[i], 2*N+2, 0);
    }
    static pair<int,int> ps[M];
    int total = 0;
    for (int i = 0; i < N; i++) {
      int x, y, n, m;
      scanf("%d %d %d %d", &x, &y, &n, &m);
      total += n;
      capacity[source][i] = n;
      capacity[i][i+N] = m;
      ps[i] = make_pair(x, y);
    }
    for (int i = 0; i < N; i++) {
      for (int j = i+1; j < N; j++) {
        if (dd(ps[i], ps[j]) < D*D) {
          capacity[i+N][j] = INF;
          capacity[j+N][i] = INF;
        }
      }
    }

    bool first = true;
    for (int i = 0; i < N; i++) {
      capacity[i][sink] = INF;
      const int r = dinic(capacity, 2*N+2, source, sink);
      if (r == total) {
        if (!first) {
          putchar(' ');
        }
        printf("%d", i);
        first = false;
      }
      capacity[i][sink] = 0;
    }
    if (first) {
      puts("-1");
    } else {
      putchar('\n');
    }
  }
  return 0;
}
