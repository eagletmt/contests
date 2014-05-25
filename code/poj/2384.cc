#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

struct state { int i, j, k, l, d; };

int main()
{
  int N;
  cin >> N;
  vector<string> grid(N);
  int gi = -100, gj = -100;
  for (int i = 0; i < N; i++) {
    cin >> grid[i];
    for (int j = 0; j < N; j++) {
      if (grid[i][j] == '*') {
        gi = i;
        gj = j;
        grid[i][j] = '.';
      }
    }
  }

  static const int INF = 10000000;
  static int dist[25][25][25][25];
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < N; j++) {
      for (int k = 0; k < N; k++) {
        fill_n(dist[i][j][k], N, INF);
      }
    }
  }
  queue<state> q;
  state init;
  init.i = gi;
  init.j = gj;
  init.d = 0;
  static const int di[] = {-1, 1, 0, 0}, dj[] = {0, 0, -1, 1};
  for (int d = 0; d < 4; d++) {
    init.k = gi - di[d];
    init.l = gj - dj[d];
    if (0 <= init.k && init.k < N && 0 <= init.l && init.l < N && grid[init.k][init.l] != '#') {
      dist[init.i][init.j][init.k][init.l] = 0;
      q.push(init);
    }
  }

  int ans = 0;
  bool valid = false;
  while (!q.empty()) {
    const state s = q.front();
    q.pop();
    ans = max(ans, s.d);

    state t;
    t.d = s.d + 1;
    for (int d = 0; d < 4; d++) {
      const int k = s.k + di[d];
      const int l = s.l + dj[d];
      if (0 <= k && k < N && 0 <= l && l < N && grid[k][l] != '#' && !(k == s.i && l == s.j)) {
        if (s.k - di[d] == s.i && s.l - dj[d] == s.j) {
          // 'push'
          valid = true;
          t.i = s.k;
          t.j = s.l;
          t.k = k;
          t.l = l;
          if (t.d < dist[t.i][t.j][t.k][t.l]) {
            dist[t.i][t.j][t.k][t.l] = t.d;
            q.push(t);
          }
        }
        t.i = s.i;
        t.j = s.j;
        t.k = k;
        t.l = l;
        if (t.d < dist[t.i][t.j][t.k][t.l]) {
          dist[t.i][t.j][t.k][t.l] = t.d;
          q.push(t);
        }
      }
    }
  }
  cout << (valid ? ans : 0) << endl;

  return 0;
}
