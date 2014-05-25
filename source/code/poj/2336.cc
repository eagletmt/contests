#include <cstdio>
#include <vector>
using namespace std;

int main()
{
  int C;
  scanf("%d", &C);
  while (C-- > 0) {
    int N, T, M;
    scanf("%d %d %d", &N, &T, &M);
    vector<int> cars(M);
    for (int i = 0; i < M; i++) {
      scanf("%d", &cars[i]);
    }

    vector<int> dp(M+1, 10000000);
    dp[0] = 0;
    vector<int> cnt(M+1);
    cnt[0] = 0;
    for (int i = 0; i <= M; i++) {
      for (int j = 1; j <= N && i+j <= M; j++) {
        const int t = max(dp[i], cars[i+j-1]) + 2*T;
        if (t < dp[i+j]) {
          dp[i+j] = t;
          cnt[i+j] = cnt[i]+1;
        }
      }
    }
    printf("%d %d\n", dp[M] - T, cnt[M]);
  }
  return 0;
}
