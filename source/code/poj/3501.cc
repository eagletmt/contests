#include <cstdio>
#include <queue>
#include <algorithm>
using namespace std;
static const int M = 1000;
static const int dx[] = {-1, 1, 0, 0}, dy[] = {0, 0, -1, 1};

int bfs(const int enemies[M][M], int X, int Y, const pair<int,int>& start, const pair<int,int>& goal, int D)
{
  if (enemies[start.first][start.second] < D) {
    return -1;
  }
  queue<pair<int,int> > q;
  q.push(start);
  static int dist[M][M];
  for (int i = 0; i < X; i++) {
    fill_n(dist[i], Y, 10000000);
  }
  dist[start.first][start.second] = 0;
  while (!q.empty()) {
    const int i = q.front().first;
    const int j = q.front().second;
    q.pop();
    for (int d = 0; d < 4; d++) {
      const int k = i + dx[d], l = j + dy[d];
      if (0 <= k && k < X && 0 <= l && l < Y && dist[i][j]+1 < dist[k][l] && enemies[k][l] >= D) {
        dist[k][l] = dist[i][j]+1;
        pair<int,int> p(k, l);
        if (p == goal) {
          return dist[k][l];
        }
        q.push(p);
      }
    }
  }
  return -1;
}

int main()
{
  int T;
  scanf("%d", &T);
  while (T-- > 0) {
    int N, X, Y;
    scanf("%d %d %d", &N, &X, &Y);
    pair<int,int> start, goal;
    scanf("%d %d %d %d", &start.first, &start.second, &goal.first, &goal.second);
    static int enemies[M][M];
    for (int i = 0; i < X; i++) {
      fill_n(enemies[i], Y, 10000000);
    }
    queue<pair<int,int> > q;
    for (int i = 0; i < N; i++) {
      int x, y;
      scanf("%d %d", &x, &y);
      enemies[x][y] = 0;
      q.push(make_pair(x, y));
    }
    while (!q.empty()) {
      const int i = q.front().first;
      const int j = q.front().second;
      q.pop();
      for (int d = 0; d < 4; d++) {
        const int k = i + dx[d], l = j + dy[d];
        if (0 <= k && k < X && 0 <= l && l < Y && enemies[i][j]+1 < enemies[k][l]) {
          enemies[k][l] = enemies[i][j]+1;
          q.push(make_pair(k, l));
        }
      }
    }

    int left = 0, right = X+Y;
    int ans = -1, dist = -1;
    while (left < right) {
      const int mid = (left + right)/2;
      const int d = bfs(enemies, X, Y, start, goal, mid);
      if (d != -1) {
        ans = mid;
        dist = d;
        left = mid+1;
      } else {
        right = mid;
      }
    }
    printf("%d %d\n", ans, dist);
  }
  return 0;
}
