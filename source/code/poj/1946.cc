#include <iostream>
#include <algorithm>
using namespace std;

int main()
{
  int N, E, D;
  cin >> N >> E >> D;
  static const int INF = 10000;
  static int dp[20][101][101];
  for (int i = 0; i < N; i++) {
    for (int j = 0; j <= E; j++) {
      fill_n(dp[i][j], D+1, INF);
    }
  }
  dp[0][0][0] = 0;
  for (int n = 0; n < N; n++) {
    for (int e = 0; e <= E; e++) {
      for (int d = 0; d <= D; d++) {
        for (int x = 1; x <= 10; x++) {
          const int dd = min(d+x, D);
          if (e+x*x <= E) {
            dp[n][e+x*x][dd] = min(dp[n][e+x*x][dd], dp[n][e][d]+1);
          }
          if (n < N-1 && d+x*x <= E) {
            dp[n+1][d+x*x][dd] = min(dp[n+1][d+x*x][dd], dp[n][e][d]+1);
          }
        }
      }
    }
  }
  int ans = INF;
  for (int i = 0; i < N; i++) {
    for (int j = 0; j <= E; j++) {
      ans = min(ans, dp[i][j][D]);
    }
  }
  cout << ans << endl;
  return 0;
}
