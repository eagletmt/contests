#include <cstdio>
#include <vector>
using namespace std;

int main()
{
  int N;
  while (scanf("%d", &N) != EOF && N != 0) {
    int H;
    scanf("%d", &H);
    const int M = 12*H;
    vector<int> f(N);
    for (int i = 0; i < N; i++) {
      scanf("%d", &f[i]);
    }
    vector<int> d(N);
    for (int i = 0; i < N; i++) {
      scanf("%d", &d[i]);
    }
    vector<int> t(N-1);
    for (int i = 0; i < N-1; i++) {
      scanf("%d", &t[i]);
    }
    vector<int> tt(N-1);
    tt[0] = t[0];
    for (int i = 1; i < N-1; i++) {
      tt[i] = tt[i-1] + t[i];
    }

    vector<vector<int> > dp(N, vector<int>(M+1, 0));
    vector<vector<int> > prev(N, vector<int>(M+1, -1));
    for (int i = 0, x = 0, r = f[0]; i <= M; i++, x += r, r = max(r - d[0], 0)) {
      dp[0][i] = x;
    }
    for (int i = 1; i < N; i++) {
      for (int j = tt[i-1]; j <= M; j++) {
        for (int k = j, x = 0, r = f[i]; k <= M; k++, x += r, r = max(r - d[i], 0)) {
          const int y = dp[i-1][j-t[i-1]] + x;
          if (y >= dp[i][k]) {
            dp[i][k] = y;
            prev[i][k] = j - t[i-1];
          }
        }
      }
    }

    int ans = 0, idx = 0;
    for (int i = 0; i < N; i++) {
      if (ans < dp[i][M]) {
        ans = dp[i][M];
        idx = i;
      }
    }
    int m = M;
    vector<int> intervals(N, 0);
    for (int i = idx; i > 0; i--) {
      intervals[i] = 5*(m - prev[i][m] - t[i-1]);
      m = prev[i][m];
    }
    printf("%d", 5*m);
    for (int i = 1; i < N; i++) {
      printf(", %d", intervals[i]);
    }
    printf("\nNumber of fish expected: %d\n\n", ans);
  }
  return 0;
}
