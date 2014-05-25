#include <iostream>
#include <vector>
#include <queue>
using namespace std;

int main()
{
  int W, H;
  while (cin >> W >> H && W != 0) {
    vector<string> grid(H);
    queue<pair<int,int> > q;
    vector<vector<int> > visited(H, vector<int>(W, false));
    for (int i = 0; i < H; i++) {
      cin >> grid[i];
      for (int j = 0; j < W; j++) {
        if (grid[i][j] == '@') {
          q.push(make_pair(i, j));
          visited[i][j] = true;
          grid[i][j] = '.';
        }
      }
    }

    int ans = 0;
    while (!q.empty()) {
      const int i = q.front().first;
      const int j = q.front().second;
      q.pop();
      ++ans;

      for (int d = 0; d < 4; d++) {
        static const int di[] = {-1, 1, 0, 0}, dj[] = {0, 0, -1, 1};
        const int k = i + di[d], l = j + dj[d];
        if (0 <= k && k < H && 0 <= l && l < W && grid[k][l] != '#' && !visited[k][l]) {
          q.push(make_pair(k, l));
          visited[k][l] = true;
        }
      }
    }
    cout << ans << endl;
  }
  return 0;
}
