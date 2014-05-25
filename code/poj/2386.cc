#include <iostream>
#include <vector>
#include <queue>
using namespace std;

int main()
{
  int N, M;
  cin >> N >> M;
  vector<string> grid(N);
  for (int i = 0; i < N; i++) {
    cin >> grid[i];
  }

  int ans = 0;
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < M; j++) {
      if (grid[i][j] == 'W') {
        queue<pair<int,int> > q;
        q.push(make_pair(i, j));
        grid[i][j] = '.';
        while (!q.empty()) {
          const pair<int,int> p = q.front();
          q.pop();
          for (int d = 0; d < 8; d++) {
            static const int di[] = {-1, -1, -1, 0, 0, 1, 1, 1};
            static const int dj[] = {-1, 0, 1, -1, 1, -1, 0, 1};
            const int k = p.first + di[d];
            const int l = p.second + dj[d];
            if (0 <= k && k < N && 0 <= l && l < M && grid[k][l] == 'W') {
              grid[k][l] = '.';
              q.push(make_pair(k, l));
            }
          }
        }
        ++ans;
      }
    }
  }
  cout << ans << endl;
  return 0;
}
