#include <cstdio>
#include <algorithm>
using namespace std;

int main()
{
  int N, L;
  scanf("%d %d", &N, &L);
  static int cows[10000];
  for (int i = 0; i < N; i++) {
    scanf("%d", &cows[i]);
  }

  const int D = (L+1 - N)/N;
  const int M = L+1 - N - (N-1)*D;
  static int dp[10001];
  static const int INF = 10000000;
  fill_n(dp, M+1, INF);
  dp[0] = cows[0];
  for (int i = 1; i < N; i++) {
    static int dp_next[10001];
    fill_n(dp_next, M+1, INF);
    for (int j = 0; j <= M; j++) {
      const int x = i + i*D + j;
      dp_next[j] = min(dp_next[j], dp[j] + abs(x - cows[i]));
      if (j < M) {
        dp_next[j+1] = min(dp_next[j+1], dp[j] + abs(x+1 - cows[i]));
      }
    }
    copy(dp_next, dp_next+M+1, dp);
  }
  printf("%d\n", dp[M]);
  return 0;
}
