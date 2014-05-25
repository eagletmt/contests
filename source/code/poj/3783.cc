#include <cstdio>
#include <algorithm>
using namespace std;

int main()
{
  static int dp[51][1001];
  for (int j = 1; j <= 1000; j++) {
    dp[1][j] = j;
  }
  for (int i = 2; i <= 50; i++) {
    for (int j = 1; j <= 1000; j++) {
      dp[i][j] = j;
      for (int k = 1; k <= j; k++) {
        dp[i][j] = min(dp[i][j], max(dp[i-1][k-1], dp[i][j-k]) + 1);
      }
    }
  }

  int P;
  scanf("%d", &P);
  while (P-- > 0) {
    int p, B, M;
    scanf("%d %d %d", &p, &B, &M);
    printf("%d %d\n", p, dp[B][M]);
  }
  return 0;
}
