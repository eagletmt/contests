#include <iostream>
#include <vector>
using namespace std;

int main()
{
  int T;
  cin >> T;
  while (T-- > 0) {
    int N, R;
    cin >> N >> R;
    vector<vector<int> > grid(N+2, vector<int>(N+2, 0));
    for (int i = 0; i < R; i++) {
      int r, c;
      cin >> r >> c;
      grid[r][c] = 1;
    }
    int r, c;
    cin >> r >> c;
    int d;
    if (r == 0) {
      d = 2;
    } else if (r == N+1) {
      d = 0;
    } else if (c == 0) {
      d = 1;
    } else if (c == N+1) {
      d = 3;
    } else {
      throw "invalid input";
    }

    static const int dr[] = {-1, 0, 1, 0}, dc[] = {0, 1, 0, -1};
    r += dr[d];
    c += dc[d];
    while (0 < r && r < N+1 && 0 < c && c < N+1) {
      if (grid[r][c]) {
        // turner
        d = (d+1)%4;
      }
      r += dr[d];
      c += dc[d];
    }
    cout << r << ' ' << c << endl;
  }
  return 0;
}
