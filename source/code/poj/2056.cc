#include <iostream>
#include <vector>
#include <queue>
using namespace std;

int main()
{
  int N, M;
  while (cin >> N >> M && N != 0) {
    vector<string> grid(N);
    for (int i = 0; i < N; i++) {
      cin >> grid[i];
    }

    static const int INF = 10000000;
    vector<vector<int> > dist(N, vector<int>(M, INF));
    queue<pair<int,int> > q;
    for (int j = M-2; j > 0; j--) {
      if (grid[0][j] == 'S') {
        dist[0][j] = 1;
        q.push(make_pair(0, j));
        break;
      } else if (grid[0][j-1] == 'S') {
        dist[0][j] = 1;
        q.push(make_pair(0, j));
      }
    }
    while (!q.empty()) {
      const int i = q.front().first;
      const int j = q.front().second;
      q.pop();
      if (i == N-1) {
        continue;
      }
      for (int d = 0; d < 3; d++) {
        static const int di[] = {0, 0, 1};
        static const int dj[] = {-1, 1, 0};
        const int k = i + di[d];
        const int l = j + dj[d];
        if (1 <= l && l < M-1
            && (grid[k][l] == 'S' || grid[k][l-1] == 'S')
            && dist[i][j]+1 < dist[k][l]) {
          dist[k][l] = dist[i][j] + 1;
          q.push(make_pair(k, l));
        }
      }
    }
    int ans = INF;
    for (int j = 1; j < M-1; j++) {
      ans = min(ans, dist[N-1][j]);
    }
    cout << ans << endl;
  }
  return 0;
}
