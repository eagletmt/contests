#include <iostream>
#include <vector>
#include <queue>
using namespace std;

int bfs(const vector<string>& grid, int x1, int y1, int x2, int y2)
{
  const int H = grid.size();
  const int W = grid[0].size();
  vector<vector<int> > dist(H, vector<int>(W, 1000000));
  queue<pair<int,int> > q;
  q.push(make_pair(y1, x1));
  dist[y1][x1] = 0;
  while (!q.empty()) {
    const int i = q.front().first;
    const int j = q.front().second;
    q.pop();
    for (int d = 0; d < 4; d++) {
      for (int s = 1;; s++) {
        static const int di[] = {-1, 1, 0, 0}, dj[] = {0, 0, -1, 1};
        const int k = i + s*di[d];
        const int l = j + s*dj[d];
        if (0 <= k && k < H && 0 <= l && l < W) {
          if (k == y2 && l == x2) {
            return dist[i][j]+1;
          }
          if (grid[k][l] == ' ' && dist[k][l] > dist[i][j]+1) {
            dist[k][l] = dist[i][j]+1;
            q.push(make_pair(k, l));
          } else {
            break;
          }
        } else {
          break;
        }
      }
    }
  }
  return -1;
}

int main()
{
  int T = 0;
  int W, H;
  while (cin >> W >> H && W != 0) {
    vector<string> grid(H+2);
    grid[0] = grid[H+1] = string(W+2, ' ');
    cin.ignore();
    for (int i = 1; i <= H; i++) {
      getline(cin, grid[i]);
      grid[i] = string(" ") + grid[i] + " ";
    }

    int x1, y1, x2, y2;
    cout << "Board #" << ++T << ":" << endl;
    int c = 0;
    while (cin >> x1 >> y1 >> x2 >> y2 && x1 != 0) {
      const int r = bfs(grid, x1, y1, x2, y2);
      cout << "Pair " << ++c << ": ";
      if (r == -1) {
        cout << "impossible." << endl;
      } else {
        cout << r << " segments." << endl;
      }
    }
    cout << endl;
  }
  return 0;
}
