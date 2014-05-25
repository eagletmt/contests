#include <iostream>
#include <algorithm>
using namespace std;

int main()
{
  int x, y;
  while (cin >> x >> y && x != -1) {
    static const int N = 24;
    static bool grid[N][N];
    for (int i = 0; i < N; i++) {
      fill_n(grid[i], N, false);
    }
    grid[x-1][y-1] = true;
    int left = 1;
    while (cin >> x >> y && x != 0) {
      grid[x-1][y-1] = true;
      ++left;
    }

    int ans = 0;
    while (left > 0) {
      ++ans;
      for (int i = 0, j = 0; i < N;) {
        bool *p = find(grid[i]+j, grid[i]+N, true);
        if (p == grid[i]+N) {
          ++i;
        } else {
          j = distance(grid[i], p);
          *p = false;
          --left;
        }
      }
    }
    cout << ans << endl;
  }
  return 0;
}
