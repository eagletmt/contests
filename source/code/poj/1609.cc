#include <cstdio>
#include <algorithm>
using namespace std;

int main()
{
  int N;
  while (scanf("%d", &N) != EOF && N != 0) {
    static int a[100][100];
    for (int i = 0; i < 100; i++) {
      fill_n(a[i], 100, 0);
    }
    for (int i = 0; i < N; i++) {
      int l, m;
      scanf("%d %d", &l, &m);
      ++a[l-1][m-1];
    }

    static int dp[100][100];
    for (int i = 0; i < 100; i++) {
      fill_n(dp[i], 100, 0);
    }
    dp[0][0] = a[0][0];
    for (int j = 1; j < 100; j++) {
      dp[0][j] = dp[0][j-1] + a[0][j];
    }
    for (int i = 1; i < 100; i++) {
      dp[i][0] = dp[i-1][0] + a[i][0];
    }
    for (int i = 1; i < 100; i++) {
      for (int j = 1; j < 100; j++) {
        dp[i][j] = max(dp[i-1][j], dp[i][j-1]) + a[i][j];
      }
    }
    printf("%d\n", dp[99][99]);
  }
  puts("*");
  return 0;
}
