#include <cstdio>
#include <algorithm>
using namespace std;

int main()
{
  char cs[16][20];
  for (int i = 0; i < 16; i++) {
    scanf("%s", cs[i]);
  }
  int prob[16][16];
  for (int i = 0; i < 16; i++) {
    for (int j = 0; j < 16; j++) {
      scanf("%d", &prob[i][j]);
    }
  }

  double dp[16][5];
  for (int i = 0; i < 16; i++) {
    fill_n(dp[i], 5, 0.0);
    dp[i][0] = 1.0;
  }
  for (int k = 1; k < 5; k++) {
    for (int i = 0; i < 16; i++) {
      for (int j = 0; j < 16; j++) {
        int x = i >> (k-1);
        int y = j >> (k-1);
        if ((x ^ y) == 1) {
          dp[i][k] += dp[i][k-1] * dp[j][k-1] * (prob[i][j] / 100.0);
        }
      }
    }
  }
  for (int i = 0; i < 16; i++) {
    printf("%-10s p=%.2f%%\n", cs[i], dp[i][4] * 100.0);
  }
  return 0;
}
