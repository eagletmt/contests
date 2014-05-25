#include <cstdio>
#include <queue>
#include <algorithm>
using namespace std;

int R, C;
char grid[1000][1001];
static const int di[] = {-1, 1, 0, 0}, dj[] = {0, 0, -1, 1};

int bfs(pair<int,int>& start)
{
  static int dist[1000][1000];
  for (int i = 0; i < R; i++) {
    fill_n(dist[i], C, 10000000);
  }
  queue<pair<int,int> > q;
  q.push(start);
  dist[start.first][start.second] = 0;
  int ans = 0;
  while (!q.empty()) {
    const int i = q.front().first;
    const int j = q.front().second;
    q.pop();
    if (dist[i][j] > ans) {
      ans = dist[i][j];
      start = make_pair(i, j);
    }
    for (int d = 0;d < 4; d++) {
      const int k = i + di[d], l = j + dj[d];
      if (grid[k][l] == '.' && dist[i][j]+1 < dist[k][l]) {
        dist[k][l] = dist[i][j]+1;
        q.push(make_pair(k, l));
      }
    }
  }
  return ans;
}

int main()
{
  int T;
  scanf("%d", &T);
  while (T-- > 0) {
    scanf("%d %d", &C, &R);
    pair<int,int> start(-1, -1);
    for (int i = 0; i < R; i++) {
      scanf("%s", grid[i]);
      for (int j = 0; start.first == -1 && j < C; j++) {
        if (grid[i][j] == '.') {
          start = make_pair(i, j);
        }
      }
    }

    bfs(start);
    printf("Maximum rope length is %d.\n", bfs(start));
  }
  return 0;
}
