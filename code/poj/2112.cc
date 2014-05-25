#include <cstdio>
#include <limits>
#include <queue>
#include <algorithm>
using namespace std;
static const int MAX_N = 232;

int edmonds_karp(const int capacity[MAX_N][MAX_N], int N, int source, int sink)/*{{{*/
{
  static int flow[MAX_N][MAX_N];
  for (int i = 0; i < N; i++) {
    fill_n(flow[i], N, 0);
  }
  int max_flow = 0;

  while (true) {
    static int parent[MAX_N];
    fill_n(parent, N, -1);
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

    int aug = numeric_limits<int>::max();
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
  int K, C, M;
  scanf("%d %d %d", &K, &C, &M);
  const int N = K+C;
  static int g[MAX_N][MAX_N];
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < N; j++) {
      scanf("%d", &g[i][j]);
      if (g[i][j] == 0) {
        g[i][j] = numeric_limits<int>::max()/N;
      }
    }
  }

  for (int k = 0; k < N; k++) {
    for (int i = 0; i < N; i++) {
      for (int j = 0; j < N; j++) {
        g[i][j] = min(g[i][j], g[i][k] + g[k][j]);
      }
    }
  }

  // binary search
  int left = 0, right = 0;
  for (int i = 0; i < K; i++) {
    right = max(right, *max_element(g[i]+K, g[i]+K+C));
  }
  while (left < right) {
    const int mid = (left + right)/2;
    static int capacity[MAX_N][MAX_N];
    // N: source
    // N+1: sink
    for (int i = 0; i < K; i++) {
      capacity[N][i] = M;
      for (int j = K; j < K+C; j++) {
        capacity[j][N+1] = 1;
        if (g[i][j] <= mid) {
          capacity[i][j] = numeric_limits<int>::max();
        } else {
          capacity[i][j] = 0;
        }
      }
    }

    const int max_flow = edmonds_karp(capacity, N+2, N, N+1);
    if (max_flow < C) {
      // ng. too short
      left = mid+1;
    } else {
      // ok
      right = mid;
    }
  }
  printf("%d\n", left);
  return 0;
}
