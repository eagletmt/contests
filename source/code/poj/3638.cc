#include <cstdio>
#include <cmath>
#include <algorithm>
using namespace std;

int main()
{
  int T;
  scanf("%d", &T);
  while (T-- > 0) {
    int H, C;
    scanf("%d %d", &H, &C);
    static int a[200];
    for (int i = 0; i < H; i++) {
      scanf("%d", &a[i]);
    }

    static double err[200][200];
    for (int i = 0; i < H; i++) {
      for (int j = i+1; j < H; j++) {
        err[i][j] = 0.0;
        double t = double(a[j] - a[i])/double(j - i);
        for (int k = i+1; k < j; k++) {
          err[i][j] += fabs(a[k] - (a[i] + t*(k - i)));
        }
      }
    }

    static double dp[200][200];
    for (int i = 0; i < 200; i++) {
      fill_n(dp[i], 200, 1e10);
    }
    dp[0][0] = 0.0;
    for (int i = 0; i < H; i++) {
      for (int j = 0; j < C-1; j++) {
        for (int k = i+1; k < H; k++) {
          dp[k][j+1] = min(dp[k][j+1], dp[i][j] + err[i][k]);
        }
      }
    }
    printf("%.4f\n", dp[H-1][C-1]/double(H));
  }
  return 0;
}
