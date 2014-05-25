#include <cstdio>
#include <algorithm>
using namespace std;

bool test(int g[20][20], int h[20][20], int H, int W)
{
  for (int i = 0; i < H; i++) {
    for (int j = 0; j < W; j++) {
      int c = 0;
      for (int d = 0; d < 8; d++) {
        static const int di[] = {-1, -1, -1, 0, 0, 1, 1, 1}, dj[] = {-1, 0, 1, -1, 1, -1, 0, 1};
        const int k = (i + di[d] + H) % H;
        const int l = (j + dj[d] + W) % W;
        c += g[k][l];
      }
      if (g[i][j]) {
        if (h[i][j] != (c == 2 || c == 3)) {
          return false;
        }
      } else {
        if (h[i][j] != (c == 3)) {
          return false;
        }
      }
    }
  }
  return true;
}

int main()
{
  int H, W;
  for (int Ti = 1; scanf("%d %d", &H, &W) != EOF && H != 0; Ti++) {
    int grid[20][20];
    for (int i = 0; i < H; i++) {
      fill_n(grid[i], W, false);
    }
    int K;
    scanf("%d", &K);
    for (int i = 0; i < K; i++) {
      int r, c;
      scanf("%d %d", &r, &c);
      grid[r][c] = true;
    }
    const int N = H*W;

    int g[20][20];
    int ans = 0;
    for (unsigned s = 0; s < (1U<<N); s++) {
      for (int i = 0; i < N; i++) {
        g[i/W][i%W] = !!(s & (1U<<i));
      }
      if (test(g, grid, H, W)) {
        ++ans;
      }
    }
    printf("Case %d: ", Ti);
    if (ans == 0) {
      puts("Garden of Eden.");
    } else {
      printf("%d possible ancestors.\n", ans);
    }
  }
  return 0;
}
