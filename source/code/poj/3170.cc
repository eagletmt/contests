#include <cstdio>
#include <queue>
using namespace std;
static const int INF = 10000000;

int W, H;
int grid[1000][1000];

void bfs(queue<pair<int,int> > q, int dist[1000][1000])
{
  while (!q.empty()) {
    const int i = q.front().first;
    const int j = q.front().second;
    q.pop();
    if (grid[i][j] == 4) {
      continue;
    }
    for (int d = 0; d < 4; d++) {
      static const int di[] = {-1, 1, 0, 0}, dj[] = {0, 0, -1, 1};
      const int k = i + di[d];
      const int l = j + dj[d];
      if (0 <= k && k < H && 0 <= l && l < W
          && (grid[k][l] != 1 && grid[k][l] != 3)
          && dist[i][j]+1 < dist[k][l]) {
        dist[k][l] = dist[i][j] + 1;
        q.push(make_pair(k, l));
      }
    }
  }
}

int main()
{
  scanf("%d %d", &W, &H);
  queue<pair<int,int> > q, qq;
  static int d[1000][1000], dd[1000][1000];
  for (int i = 0; i < H; i++) {
    for (int j = 0; j < W; j++) {
      scanf("%d", &grid[i][j]);
      if (grid[i][j] == 2) {
        q.push(make_pair(i, j));
        d[i][j] = 0;
      } else {
        d[i][j] = INF;
      }
      if (grid[i][j] == 3) {
        qq.push(make_pair(i, j));
        dd[i][j] = 0;
      } else {
        dd[i][j] = INF;
      }
    }
  }
  bfs(q, d);
  bfs(qq, dd);
  int ans = INF;
  for (int i = 0; i < H; i++) {
    for (int j = 0; j < W; j++) {
      if (grid[i][j] == 4) {
        ans = min(ans, d[i][j] + dd[i][j]);
      }
    }
  }
  printf("%d\n", ans);
  return 0;
}
