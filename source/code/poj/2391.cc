#include <cstdio>
#include <queue>
#include <limits>
#include <algorithm>
using namespace std;
static const long long INF = 1LL<<60;
static const int MAXF = 200;

int F, P;
long long dist[MAXF][MAXF];
int initial_cows[MAXF];
int shelter[MAXF];

static const int MAXN = 2*MAXF+2;

template <class T>
T dinic_augment(const T capacity[MAXN][MAXN], int N, T flow[MAXN][MAXN], int level[MAXN], bool finished[MAXN], int u, int sink, T cur)/*{{{*/
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
      const T f = dinic_augment(capacity, N, flow, level, finished, v, sink, min(cur, capacity[u][v] - flow[u][v]));
      if (f > 0) {
        flow[u][v] += f;
        flow[v][u] -= f;
        finished[u] = false;
        return f;
      }
    }
  }
  return 0;
}/*}}}*/

// O(V^2 E)
template <typename T>
T dinic(const T capacity[MAXN][MAXN], int N, int source, int sink)/*{{{*/
{
  static T flow[MAXN][MAXN];
  for (int i = 0; i < N; i++) {
    fill_n(flow[i], N, 0);
  }
  T max_flow = 0;

  while (true) {
    static int level[MAXN];
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

    static bool finished[MAXN];
    fill_n(finished, MAXN, false);
    bool updated = false;
    while (true) {
      const T f = dinic_augment(capacity, N, flow, level, finished, source, sink, INF);
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

bool ok(long long limit)
{
  const int source = 2*F, sink = 2*F+1;
  const int N = 2*F+2;
  static long long capacity[MAXN][MAXN];
  for (int i = 0; i < N; i++) {
    fill_n(capacity[i], N, 0);
  }

  for (int i = 0; i < F; i++) {
    for (int j = 0; j < F; j++) {
      if (dist[i][j] <= limit) {
        capacity[i][F+j] = INF;
      } else {
        capacity[i][F+j] = 0;
      }
    }
  }
  long long total = 0;
  for (int i = 0; i < F; i++) {
    capacity[source][i] = initial_cows[i];
    capacity[F+i][sink] = shelter[i];
    total += initial_cows[i];
  }
  return dinic(capacity, N, source, sink) == total;
}

int main()
{
  scanf("%d %d", &F, &P);
  int cows = 0, shels = 0;
  for (int i = 0; i < F; i++) {
    scanf("%d %d", &initial_cows[i], &shelter[i]);
    cows += initial_cows[i];
    shels += shelter[i];
  }
  for (int i = 0; i < F; i++) {
    fill_n(dist[i], F, INF);
    dist[i][i] = 0;
  }
  for (int i = 0; i < P; i++) {
    int u, v;
    long long d;
    scanf("%d %d %lld", &u, &v, &d);
    --u;  --v;
    dist[u][v] = min(dist[u][v], d);
    dist[v][u] = min(dist[v][u], d);
  }

  for (int k = 0; k < F; k++) {
    for (int i = 0; i < F; i++) {
      for (int j = 0; j < F; j++) {
        dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
      }
    }
  }

  long long hi = INF, lo = 0;
  while (lo < hi) {
    const long long mid = (lo + hi)/2LL;
    if (ok(mid)) {
      hi = mid;
    } else {
      lo = mid+1;
    }
  }
  if (lo == INF) {
    puts("-1");
  } else {
    printf("%lld\n", lo);
  }
  return 0;
}
