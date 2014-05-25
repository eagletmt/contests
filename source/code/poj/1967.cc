#include <cstdio>
#include <algorithm>
using namespace std;

int main()
{
  int N;
  while (scanf("%d", &N) != EOF) {
    static const int MAXN = 10000;
    static const int INF = 100000000;
    static pair<int,int> a[MAXN];
    for (int i = 0; i < N; i++) {
      scanf("%d %d", &a[i].first, &a[i].second);
    }
    static int dpL[MAXN], dpR[MAXN];
    for (int i = N-1; i >= 0; i--) {
      static int prevL[MAXN], prevR[MAXN];
      fill_n(dpL, N, INF);
      fill_n(dpR, N, INF);
      dpL[i] = dpR[i] = 0;
      for (int j = i+1; j < N; j++) {
        if (i+1 < N) {
          const int x = min(prevL[j] + a[i+1].first - a[i].first, prevR[j] + a[j].first - a[i].first);
          if (x < a[i].second) {
            dpL[j] = x;
          }
          dpL[j] = min(dpL[j], INF);
        }
        if (j > 0) {
          const int x = min(dpR[j-1] + a[j].first - a[j-1].first, dpL[j-1] + a[j].first - a[i].first);
          if (x < a[j].second) {
            dpR[j] = x;
          }
          dpR[j] = min(dpR[j], INF);
        }
      }
      copy(dpL+i, dpL+N, prevL+i);
      copy(dpR+i, dpR+N, prevR+i);
    }
    const int ans = min(dpL[N-1], dpR[N-1]);
    if (ans >= INF) {
      puts("No solution");
    } else {
      printf("%d\n", ans);
    }
  }
  return 0;
}
