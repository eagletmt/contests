#include <cstdio>
#include <vector>
using namespace std;

int main()
{
  int M, N, L;
  scanf("%d %d %d", &M, &N, &L);
  vector<int> clubs(L);
  vector<vector<int> > adj(N);
  for (int i = 0; i < L; i++) {
    scanf("%d", &clubs[i]);
    --clubs[i];
  }

  static const int INF = 10000000;
  vector<vector<int> > dist(M, vector<int>(M, INF));
  for (int i = 0; i < M; i++) {
    dist[i][i] = 0;
  }
  vector<int> walls(N*N, -10);
  for (int i = 0; i < M; i++) {
    int T;
    scanf("%d", &T);
    vector<int> towns(T);
    for (int j = 0; j < T; j++) {
      scanf("%d", &towns[j]);
      --towns[j];
      adj[towns[j]].push_back(i);
    }
    for (int j = 0; j < T; j++) {
      int n = towns[j], m = towns[(j+1)%T];
      if (n > m) {
        swap(n, m);
      }
      const int w = n*N + m;
      if (walls[w] < 0) {
        walls[w] = i;
      } else {
        const int u = walls[w];
        dist[u][i] = dist[i][u] = 1;
      }
    }
  }

  for (int k = 0; k < M; k++) {
    for (int i = 0; i < M; i++) {
      for (int j = 0; j < M; j++) {
        dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
      }
    }
  }
  int ans = INF;
  for (int i = 0; i < M; i++) {
    int s = 0;
    for (vector<int>::const_iterator it = clubs.begin(); it != clubs.end(); ++it) {
      int x = INF;
      for (vector<int>::const_iterator jt = adj[*it].begin(); jt != adj[*it].end(); ++jt) {
        x = min(x, dist[i][*jt]);
      }
      s += x;
    }
    ans = min(ans, s);
  }
  printf("%d\n", ans);

  return 0;
}
