#include <cstdio>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

static const int N = 310;
static const int INF = 10000000;
static int grid[N][N];

int solve()
{
  if (grid[1][1] == 0) {
    return -1;
  }

  static int dist[N][N];
  for (int i = 0; i < N; i++) {
    fill_n(dist[i], N, INF);
  }
  queue<pair<int,int> > q;
  q.push(make_pair(1, 1));
  dist[1][1] = 0;

  while (!q.empty()) {
    const int x = q.front().first;
    const int y = q.front().second;
    q.pop();
    if (grid[x][y] == INF) {
      return dist[x][y];
    }
    for (int d = 0; d < 4; d++) {
      static const int dx[] = {-1, 1, 0, 0};
      static const int dy[] = {0, 0, -1, 1};
      const int k = x + dx[d];
      const int l = y + dy[d];
      const int dd = dist[x][y]+1;
      if (1 <= k && 1 <= l) {
        if (dd < grid[k][l] && dd < dist[k][l]) {
          dist[k][l] = dd;
          q.push(make_pair(k, l));
        }
      }
    }
  }
  return -1;
}

int main()
{
  for (int i = 0; i < N; i++) {
    fill_n(grid[i], N, INF);
  }

  int M;
  scanf("%d", &M);
  for (int i = 0; i < M; i++) {
    int X, Y, T;
    scanf("%d %d %d", &X, &Y, &T);
    ++X;  ++Y;
    for (int d = 0; d < 5; d++) {
      static const int dx[] = {0, -1, 1, 0, 0};
      static const int dy[] = {0, 0, 0, -1, 1};
      int& g = grid[X+dx[d]][Y+dy[d]];
      g = min(g, T);
    }
  }

  printf("%d\n", solve());
  return 0;
}
