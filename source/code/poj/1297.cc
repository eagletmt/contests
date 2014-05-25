#include <cstdio>
#include <utility>
#include <algorithm>
using namespace std;
static const double INF = 100000 * 200;
int M, N;
int order[100];
pair<int,double> shops[100000];

double solve()
{
  static double dp[100000];
  dp[0] = shops[0].first == order[0] ? shops[0].second : INF;
  for (int j = 1; j < N; j++) {
    if (shops[j].first == order[0]) {
      dp[j] = min(dp[j-1], shops[j].second);
    } else {
      dp[j] = dp[j-1];
    }
  }

  static double dp_next[100000];
  for (int i = 1; i < M; i ++) {
    fill_n(dp_next, N, INF);
    for (int j = i; j < N; j++) {
      if (shops[j].first == order[i]) {
        dp_next[j] = min(dp_next[j-1], dp[j-1] + shops[j].second);
      } else {
        dp_next[j] = dp_next[j-1];
      }
    }
    copy(dp_next, dp_next + N, dp);
  }

  return dp[N-1];
}

int main()
{
  while (scanf("%d %d", &M, &N) != EOF && M != 0) {
    for (int i = 0; i < M; i++) {
      scanf("%d", &order[i]);
    }
    for (int i = 0; i < N; i++) {
      scanf("%d %lf", &shops[i].first, &shops[i].second);
    }

    const double ans = solve();
    if (ans >= INF) {
      puts("Impossible");
    } else {
      printf("%.2f\n", ans);
    }
  }
  return 0;
}
