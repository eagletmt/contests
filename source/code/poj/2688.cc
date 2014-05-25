#include <cstdio>
#include <queue>
#include <algorithm>
using namespace std;

int H, W;
char grid[20][20];

int bfs(const pair<int,int>& start, const pair<int,int>& goal)
{
  queue<pair<pair<int,int>,int> > q;
  q.push(make_pair(start, 0));
  static bool visited[20][20];
  for (int i = 0; i < H; i++) {
    fill_n(visited[i], W, false);
  }
  visited[start.first][start.second] = true;
  while (!q.empty()) {
    const pair<pair<int,int>,int> p = q.front();
    q.pop();
    if (p.first == goal) {
      return p.second;
    }

    for (int d = 0; d < 4; d++) {
      static const int dir_i[] = {0, 0, -1, 1};
      static const int dir_j[] = {-1, 1, 0, 0};
      const int i = p.first.first + dir_i[d];
      const int j = p.first.second + dir_j[d];
      if (0 <= i && i < H && 0 <= j && j < W && !visited[i][j] && grid[i][j] != 'x') {
        visited[i][j] = true;
        q.push(make_pair(make_pair(i, j), p.second+1));
      }
    }
  }
  return 1000000;
}

int main()
{
  while (scanf("%d %d", &W, &H) == 2 && W != 0) {
    pair<int,int> nodes[11];
    int N = 0;
    pair<int,int> robot;
    for (int i = 0; i < H; i++) {
      scanf("%s", grid[i]);
      for (int j = 0; j < W; j++) {
        if (grid[i][j] == '*') {
          nodes[N].first = i;
          nodes[N].second = j;
          ++N;
        } else if (grid[i][j] == 'o') {
          robot.first = i;
          robot.second = j;
        }
      }
    }

    nodes[N++] = robot;
    static int weights[11][11];
    for (int i = 0; i < N; i++) {
      fill_n(weights[i], N, 0);
    }
    for (int i = 0; i < N; i++) {
      for (int j = i+1; j < N; j++) {
        weights[i][j] = weights[j][i] = bfs(nodes[i], nodes[j]);
      }
    }

    static int dp[1<<11][11];
    for (int s = 0; s < (1<<N); s++) {
      fill_n(dp[s], N, 1000000);
    }
    for (int i = 0; i < N; i++) {
      dp[1<<i][i] = weights[N-1][i];
    }
    for (int s = 0; s < (1<<N); s++) {
      for (int i = 0; i < N; i++) {
        if ((s & (1<<i)) == 0) { continue; }
        for (int j = 0; j < N; j++) {
          if ((s & (1<<j)) != 0) { continue; }
          const int t = s | (1<<j);
          dp[t][j] = min(dp[t][j], dp[s][i] + weights[i][j]);
        }
      }
    }

    int ans = 1000000;
    for (int i = 0; i < N-1; i++) {
      ans = min(ans, dp[((1<<N)-1)][i]);
    }
    if (ans >= 1000000) {
      puts("-1");
    } else {
      printf("%d\n", ans);
    }
  }
  return 0;
}
