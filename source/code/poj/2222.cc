#include <iostream>
#include <vector>
using namespace std;

bool ok(char board[10][10], int H, int W)
{
  for (int i = 0; i < H; i++) {
    for (int j = 0; j < W; j++) {
      switch (board[i][j]) {
        case 'K':
          for (int d = 0; d < 8; d++) {
            static const int di[] = {-1, -1, -1, 0, 0, 1, 1, 1}, dj[] = {-1, 0, 1, -1, 1, -1, 0, 1};
            const int k = i + di[d], l = j + dj[d];
            if (0 <= k && k < H && 0 <= l && l < W && board[k][l] != 'E') {
              return false;
            }
          }
          break;
        case 'Q':
          for (int d = 0; d < 8; d++) {
            static const int di[] = {-1, -1, -1, 0, 0, 1, 1, 1}, dj[] = {-1, 0, 1, -1, 1, -1, 0, 1};
            int k = i + di[d], l = j + dj[d];
            while (0 <= k && k < H && 0 <= l && l < W) {
              if (board[k][l] != 'E') {
                return false;
              }
              k += di[d];
              l += dj[d];
            }
          }
          break;
        case 'R':
          for (int d = 0; d < 4; d++) {
            static const int di[] = {-1, 0, 1, 0}, dj[] = {0, 1, 0, -1};
            int k = i + di[d], l = j + dj[d];
            while (0 <= k && k < H && 0 <= l && l < W) {
              if (board[k][l] != 'E') {
                return false;
              }
              k += di[d];
              l += dj[d];
            }
          }
          break;
        case 'B':
          for (int d = 0; d < 4; d++) {
            static const int di[] = {-1, -1, 1, 1}, dj[] = {-1, 1, 1, -1};
            int k = i + di[d], l = j + dj[d];
            while (0 <= k && k < H && 0 <= l && l < W) {
              if (board[k][l] != 'E') {
                return false;
              }
              k += di[d];
              l += dj[d];
            }
          }
          break;
        case 'N':
          for (int d = 0; d < 8; d++) {
            static const int di[] = {-1, -2, -2, -1, 1, 2, 2, 1}, dj[] = {-2, -1, 1, 2, 2, 1, -1, -2};
            const int k = i + di[d], l = j + dj[d];
            if (0 <= k && k < H && 0 <= l && l < W && board[k][l] != 'E') {
              return false;
            }
          }
          break;
      }
    }
  }
  return true;
}

int main()
{
  for (string dummy; cin >> dummy;) {
    int W, H;
    cin >> W >> H;
    char board[10][10];
    vector<int> xs, ys;
    vector<char> cs;
    for (int i = 0; i < H; i++) {
      for (int j = 0; j < W; j++) {
        cin >> board[i][j];
        if (board[i][j] != 'E') {
          xs.push_back(i);
          ys.push_back(j);
          cs.push_back(board[i][j]);
        }
      }
    }
    cin >> dummy;

    const int N = xs.size();
    int ans = 20;
    for (unsigned s = 0; s < (1U<<N); s++) {
      const int n = __builtin_popcount(s);
      if (n >= ans) {
        continue;
      }
      for (int i = 0; i < N; i++) {
        if (s & (1U<<i)) {
          board[xs[i]][ys[i]] = 'E';
        }
      }
      if (ok(board, H, W)) {
        ans = min(ans, n);
      }
      for (int i = 0; i < N; i++) {
        board[xs[i]][ys[i]] = cs[i];
      }
    }
    cout << "Minimum Number of Pieces to be removed: " << ans << endl;
  }
  return 0;
}
