#include <cstdio>
#include <algorithm>
using namespace std;

int main()
{
  int N;
  scanf("%d", &N);
  static const int MAXN = 30000;
  static int a[MAXN];
  for (int i = 0; i < N; i++) {
    scanf("%d", &a[i]);
    --a[i];
  }

  static int dp1[MAXN][3], dp2[MAXN][3];
  static const int INF = 10000000;
  for (int i = 0; i < N; i++) {
    fill_n(dp1[i], 3, INF);
    fill_n(dp2[i], 3, INF);
  }
  for (int j = 0; j < 3; j++) {
    dp1[0][j] = dp2[0][j] = j == a[0] ? 0 : 1;
  }
  for (int i = 1; i < N; i++) {
    for (int j = 0; j < 3; j++) {
      const int c = j == a[i] ? 0 : 1;
      for (int k = 0; k <= j; k++) {
        dp1[i][j] = min(dp1[i][j], dp1[i-1][k] + c);
      }
      for (int k = j; k < 3; k++) {
        dp2[i][j] = min(dp2[i][j], dp2[i-1][k] + c);
      }
    }
  }
  int ans = INF;
  for (int j = 0; j < 3; j++) {
    ans = min(ans, dp1[N-1][j]);
    ans = min(ans, dp2[N-1][j]);
  }
  printf("%d\n", ans);
  return 0;
}
