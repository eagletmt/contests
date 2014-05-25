#include <cstdio>
#include <algorithm>
using namespace std;

int main()
{
  int N;
  while (scanf("%d", &N) != EOF && N != 0) {
    static int p[201], q[201];
    for (int i = 1; i <= N; i++) {
      scanf("%d", &p[i]);
    }
    for (int i = 0; i <= N; i++) {
      scanf("%d", &q[i]);
    }

    static int sums[202];
    for (int i = 0; i <= N; i++) {
      sums[i+1] = p[i] + q[i] + sums[i];
    }
    static int dp[201][201];
    for (int i = 0; i <= N; i++) {
      fill_n(dp[i], N+1, 100000000);
      dp[i][i] = 0;
    }
    for (int d = 1; d <= N; d++) {
      for (int i = 0; i+d <= N; i++) {
        const int j = i + d;
        for (int k = i; k+1 <= j; k++) {
          dp[i][j] = min(dp[i][j], dp[i][k] + dp[k+1][j] + sums[j+1] - sums[i] - p[i]);
        }
      }
    }
    printf("%d\n", dp[0][N]);
  }
  return 0;
}
