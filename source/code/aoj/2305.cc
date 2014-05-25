#include <iostream>
#include <cstdio>
#include <cmath>
#include <algorithm>
using namespace std;
static const int M = 200000;

int main()
{
  int N;
  cin >> N;
  int a[20];
  for (int i = 0; i < N; i++) {
    cin >> a[i];
  }

  static double dp[20][M];
  for (int i = 0; i < N; i++) {
    fill_n(dp[i], M, 1e10);
  }
  for (int i = 1; i < M; i++) {
    dp[0][i] = fabs(a[0] - i)/double(a[0]);
  }
  for (int i = 0; i < N-1; i++) {
    for (int j = 1; j < M; j++) {
      for (int k = 1; k*j < M; k++) {
        dp[i+1][k*j] = min(dp[i+1][k*j], max(dp[i][j], fabs(a[i+1] - k*j)/double(a[i+1])));
      }
    }
  }

  double ans = 1e10;
  for (int i = 1; i < M; i++) {
    ans = min(ans, dp[N-1][i]);
  }
  printf("%.9f\n", ans);
  return 0;
}
