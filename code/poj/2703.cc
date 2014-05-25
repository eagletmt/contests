#include <cstdio>
#include <algorithm>
using namespace std;

struct rect
{
  int w, h;
  bool operator<(const rect& r) const
  {
    if (w == r.w) {
      return h > r.h;
    } else {
      return w < r.w;
    }
  }
};

int main()
{
  int N;
  while (scanf("%d", &N) != EOF && N != -1) {
    static rect v[1001];
    v[0].w = v[0].h = 0;
    for (int i = 1; i <= N; i++) {
      scanf("%d %d", &v[i].w, &v[i].h);
    }
    sort(v, v+N+1);

    static int dp[1001][1001];
    for (int i = 0; i <= N; i++) {
      fill_n(dp[i], N+1, 0);
    }

    int ans = 0;
    for (int i = 0; i < N; i++) {
      for (int j = 0; j < N; j++) {
        const int k = max(i, j) + 1;
        // put vertical
        dp[k][j] = max(dp[k][j], dp[i][j] + (v[k].w-v[i].w) * (v[k].h-v[j].w));
        // put horizontal
        dp[i][k] = max(dp[i][k], dp[i][j] + (v[k].h-v[i].w) * (v[k].w-v[j].w));
        if (k == N) {
          ans = max(ans, dp[k][j]);
          ans = max(ans, dp[i][k]);
        }
      }
    }
    printf("%d\n", ans);
  }
  return 0;
}
