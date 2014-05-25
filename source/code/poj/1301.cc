#include <cstdio>
#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

struct triplet
{
  int i, j, k;
  triplet(int a, int b, int c) : i(a), j(b), k(c) {}
};

int main()
{
  for (string s; cin >> s && s != "ENDOFINPUT";) {
    int C, R;
    cin >> C >> R;
    vector<string> m(R);
    for (int i = 0; i < R; i++) {
      cin >> m[i];
    }
    cin >> s;

    queue<triplet> q;
    static const int INF = 10000000;
    static bool grid[10][10][4];
    static int dist[10][10][4];
    for (int i = 0; i < R; i++) {
      for (int j = 0; j < C; j++) {
        fill_n(dist[i][j], 4, INF);
        fill_n(grid[i][j], 4, true);
      }
    }
    for (int i = 0; i < R; i++) {
      for (int j = 0; j < C; j++) {
        switch (m[i][j]) {
          case 'L':
            dist[i][j][0] = 0;
            q.push(triplet(i, j, 0));
            break;
          case 'S':
            for (int k = 0; k < 4; k++) {
              static const int dr[] = {-1, 0, 1, 0};
              static const int dc[] = {0, 1, 0, -1};
              for (int x = i, y = j; 0 <= x && x < R && 0 <= y && y < C; x += dr[k], y += dc[k]) {
                grid[x][y][k] = false;
              }
            }
            break;
          case 'P':
            fill_n(grid[i][j], 4, false);
            break;
        }
      }
    }

    while (!q.empty()) {
      const int r = q.front().i;
      const int c = q.front().j;
      const int t = q.front().k;
      q.pop();
      if (!grid[r][c][t]) {
        continue;
      }
      if (m[r][c] == 'G') {
        cout << "FERRET" << endl;
        goto NEXT;
      }
      for (int d = -1; d <= 1; d++) {
        const int i = r+1;
        const int j = c+d;
        const int dd = dist[r][c][t]+1;
        const int k = dd % 4;
        if (0 <= i && i < R && 0 <= j && j < C && grid[i][j][t] && grid[i][j][k] && dd < dist[i][j][k]) {
          dist[i][j][k] = dd;
          q.push(triplet(i, j, k));
        }
      }
    }
    cout << "GARRET" << endl;
NEXT:
    ;
  }
  return 0;
}
