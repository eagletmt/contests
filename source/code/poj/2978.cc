#include <iostream>
#include <algorithm>
using namespace std;

int main()
{
  int M, K;
  while (cin >> M >> K && M != 0) {
    static int dp[100][5][1<<5];
    static const int INF = 10000000;
    for (int i = 0; i < M; i++) {
      for (int j = 0; j < K; j++) {
        fill_n(dp[i][j], 1<<K, INF);
      }
    }

    static int a[100];
    for (int i = 0; i < M; i++) {
      cin >> a[i];
      --a[i];
    }

    for (int j = 0; j < K; j++) {
      if (j == a[0]) {
        dp[0][j][1<<j] = 0;
      } else {
        dp[0][j][1<<j] = 1;
      }
    }
    for (int i = 0; i < M-1; i++) {
      for (int j = 0; j < K; j++) {
        for (int k = 0; k < (1<<K); k++) {
          if (!(k & (1<<j))) {
            continue;
          }
          dp[i+1][j][k] = min(dp[i+1][j][k], dp[i][j][k] + (a[i+1] != j));
          if (!(k & (1<<a[i+1]))) {
            const int s = k | (1<<a[i+1]);
            dp[i+1][a[i+1]][s] = min(dp[i+1][a[i+1]][s], dp[i][j][k]);
          }
        }
      }
    }

    int ans = INF;
    for (int j = 0; j < K; j++) {
      for (int k = 0; k < (1<<K); k++) {
        ans = min(ans, dp[M-1][j][k]);
      }
    }
    cout << ans << endl;
  }
  return 0;
}
