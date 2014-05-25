#include <cstdio>
#include <algorithm>
using namespace std;

int main()
{
  int N, T, S;
  scanf("%d %d %d", &N, &T, &S);
  static int as[3001], bs[3001];
  for (int i = 1; i <= N; i++) {
    scanf("%d %d", &as[i], &bs[i]);
  }

  static int dp[3001][3001];
  int ans = 0;
  for (int i = 1; i <= N; i++) {
    for (int j = 1; j <= T; j++) {
      dp[i][j] = max(dp[i-1][j], dp[i][j-1]);
      const int beg = j-bs[i];
      if (beg >= 0 && (S <= beg || j <= S)) {
        dp[i][j] = max(dp[i][j], dp[i-1][beg] + as[i]);
      }
      ans = max(ans, dp[i][j]);
    }
  }
  printf("%d\n", ans);
  return 0;
}
