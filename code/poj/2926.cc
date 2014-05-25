#include <cstdio>
#include <algorithm>
using namespace std;

int main()
{
  static const int K = 5;
  static const double INF = 1e15;
  int N;
  scanf("%d", &N);
  double a[1<<K];
  fill_n(a, 1<<K, -INF);
  for (int i = 0; i < N; i++) {
    double xs[K];
    for (int j = 0; j < K; j++) {
      scanf("%lf", &xs[j]);
    }
    for (unsigned s = 0; s < (1<<K); s++) {
      double y = 0;
      for (int j = 0; j < K; j++) {
        if (s & (1<<j)) {
          y += xs[j];
        } else {
          y -= xs[j];
        }
      }
      a[s] = max(a[s], y);
    }
  }

  double ans = -INF;
  for (unsigned s = 0; s < (1<<K); s++) {
    unsigned t = ~s & ((1<<K)-1);
    ans = max(ans, a[s] + a[t]);
  }
  printf("%.2f\n", ans);
  return 0;
}
