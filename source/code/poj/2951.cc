#include <iostream>
#include <algorithm>
using namespace std;

int memo[21][21][21];

int solve(int W, int H, int M)
{
  if (W > H) {
    swap(W, H);
  }
  int& ans = memo[W][H][M];
  if (ans != 0) {
    return ans;
  } else if (M == 1) {
    ans = W*H;
    return ans;
  } else {
    ans = W*H;
    for (int i = 1; i < W; i++) {
      for (int j = 1; j < M; j++) {
        const int x = solve(i, H, j);
        const int y = solve(W-i, H, M-j);
        ans = min(ans, max(x, y));
      }
    }
    for (int i = 1; i < H; i++) {
      for (int j = 1; j < M; j++) {
        const int x = solve(W, i, j);
        const int y = solve(W, H-i, M-j);
        ans = min(ans, max(x, y));
      }
    }
    return ans;
  }
}

int main()
{
  int W, H, M;
  while (cin >> W >> H >> M && M != 0) {
    cout << solve(W, H, M) << endl;
  }
  return 0;
}
