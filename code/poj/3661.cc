#include <cstdio>
#include <algorithm>
using namespace std;

int main()
{
  int N, M;
  scanf("%d %d", &N, &M);
  static int D[10000];
  for (int i = 0; i < N; i++) {
    scanf("%d", &D[i]);
  }

  static int dp[10001][501];
  static int INF = 10000000;
  for (int i = 0; i <= N; i++) {
    fill_n(dp[i], M+1, -INF);
  }
  dp[0][0] = 0;
  for (int i = 0; i < N; i++) {
    for (int j = 0; j <= M; j++) {
      // choose rest
      const int k = j == 0 ? i+1 : i+j;
      if (k <= N) {
        dp[k][0] = max(dp[k][0], dp[i][j]);
      }

      // choose run
      if (j < M) {
        dp[i+1][j+1] = max(dp[i+1][j+1], dp[i][j] + D[i]);
      }
    }
  }
  printf("%d\n", dp[N][0]);
  return 0;
}
