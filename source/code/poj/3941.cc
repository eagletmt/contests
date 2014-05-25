#include <cstdio>
#include <algorithm>
using namespace std;

int main()
{
  int N, M, K;
  while (scanf("%d %d %d", &N, &M, &K) != EOF && N != 0) {
    static double dp[10001], dp_next[10001];
    fill_n(dp, N*M+1, 0.0);
    dp[0] = 1.0;
    for (int i = 0; i < N; i++) {
      fill_n(dp_next, N*M+1, 0.0);
      for (int j = 0; j < N*M; j++) {
        for (int k = 1; k <= M; k++) {
          dp_next[j+k] += dp[j] * 1.0/M;
        }
      }
      swap(dp, dp_next);
    }
    double ans = 0;
    for (int i = 0; i <= N*M; i++) {
      if (i <= K) {
        ans += dp[i];
      } else {
        ans += dp[i] * (i-K);
      }
    }
    printf("%.8f\n", ans);
  }
  return 0;
}
