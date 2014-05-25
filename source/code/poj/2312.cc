#include <iostream>
#include <vector>
#include <queue>
using namespace std;

int main()
{
  int M, N;
  while (cin >> M >> N && M != 0) {
    vector<string> grid(M);
    pair<int,int> start, goal;
    for (int i = 0; i < M; i++) {
      cin >> grid[i];
      for (int j = 0; j < N; j++) {
        if (grid[i][j] == 'Y') {
          start = make_pair(i, j);
          grid[i][j] = 'E';
        } else if (grid[i][j] == 'T') {
          goal = make_pair(i, j);
          grid[i][j] = 'E';
        }
      }
    }

    priority_queue<pair<int, pair<int,int> > > q;
    static const int INF = 10000000;
    vector<vector<int> > dist(M, vector<int>(N, INF));
    q.push(make_pair(0, start));
    dist[start.first][start.second] = 0;
    while (!q.empty() && q.top().second != goal) {
      const int c = -q.top().first;
      const int i = q.top().second.first;
      const int j = q.top().second.second;
      q.pop();
      if (c > dist[i][j]) {
        continue;
      }
      for (int d = 0; d < 4; d++) {
        static const int di[] = {-1, 1, 0, 0}, dj[] = {0, 0, -1, 1};
        const int k = i + di[d], l = j + dj[d];
        if (0 <= k && k < M && 0 <= l && l < N && grid[k][l] != 'R' && grid[k][l] != 'S') {
          const int cc = dist[i][j] + (grid[k][l] == 'B' ? 2 : 1);
          if (cc < dist[k][l]) {
            dist[k][l] = cc;
            q.push(make_pair(-cc, make_pair(k, l)));
          }
        }
      }
    }

    if (dist[goal.first][goal.second] == INF) {
      cout << "-1" << endl;
    } else {
      cout << dist[goal.first][goal.second] << endl;
    }
  }
  return 0;
}
