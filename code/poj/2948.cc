#include <cstdio>
#include <algorithm>
using namespace std;

int main()
{
  int N, M;
  while (scanf("%d %d", &N, &M) != EOF && N != 0) {
    static int left[500][501];
    for (int i = 0; i < N; i++) {
      left[i][0] = 0;
      for (int j = 1; j <= M; j++) {
        scanf("%d", &left[i][j]);
        left[i][j] += left[i][j-1];
      }
    }
    static int up[500][501];
    for (int i = 0; i < N; i++) {
      up[i][0] = 0;
      for (int j = 0; j < M; j++) {
        scanf("%d", &up[i][j]);
      }
      up[i][M] = 0;
      for (int j = M-1; j >= 0; j--) {
        up[i][j] += up[i][j+1];
      }
    }

    static int dp[500][501];
    for (int i = 0; i < N; i++) {
      fill_n(dp[i], M+1, 0);
    }
    for (int j = 0; j <= M; j++) {
      dp[0][j] = left[0][j] + up[0][j];
    }
    for (int i = 1; i < N; i++) {
      for (int j = 0; j <= M; j++) {
        dp[i][j] = 0;
        for (int k = 0; k <= j; k++) {
          dp[i][j] = max(dp[i][j], dp[i-1][k] + left[i][j] + up[i][j]);
        }
      }
    }
    printf("%d\n", *max_element(dp[N-1], dp[N-1]+M+1));
  }
  return 0;
}
