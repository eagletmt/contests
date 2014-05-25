#include <cstdio>
#include <algorithm>
using namespace std;
static const int K = 1000;

bool bm_augment(const bool g[K][K], int N, int u, int *match_to, bool *visited) // {{{
{
  if (u < 0) {
    return true;
  }

  for (int v = 0; v < N; v++) {
    if (g[u][v] && !visited[v]) {
      visited[v] = true;
      if (bm_augment(g, N, match_to[v], match_to, visited)) {
        match_to[u] = v;
        match_to[v] = u;
        return true;
      }
    }
  }
  return false;
} // }}}

int bipartite_matching(const bool g[K][K], int N)  // {{{
{
  static int match_to[K];
  fill_n(match_to, N, -1);
  int match = 0;
  for (int u = 0; u < N; u++) {
    static bool visited[K];
    fill_n(visited, N, false);
    if (bm_augment(g, N, u, match_to, visited)) {
      match++;
    }
  }
  return match;
} // }}}

int main()
{
  int N, M;
  while (scanf("%d %d", &N, &M) != EOF && N != 0) {
    static bool dist[500][500];
    for (int i = 0; i < N; i++) {
      fill_n(dist[i], N, false);
    }
    for (int i = 0; i < M; i++) {
      int u, v;
      scanf("%d %d", &u, &v);
      --u;  --v;
      dist[u][v] = true;
    }

    for (int k = 0; k < N; k++) {
      for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
          if (dist[i][k] && dist[k][j]) {
            dist[i][j] = true;
          }
        }
      }
    }

    static bool g[K][K];
    for (int i = 0; i < 2*N; i++) {
      fill_n(g[i], 2*N, false);
    }
    for (int i = 0; i < N; i++) {
      for (int j = 0; j < N; j++) {
        if (dist[i][j]) {
          g[i][j+N] = true;
        }
      }
    }
    const int r = bipartite_matching(g, 2*N);
    printf("%d\n", N-r);
  }
  return 0;
}
