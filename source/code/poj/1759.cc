#include <cstdio>
#include <algorithm>
using namespace std;

pair<double, bool> f(int N, double h0, double h1)
{
  for (int i = 2; i < N; i++) {
    double h = 2*h1 - h0 + 2;
    if (h < 0) {
      return make_pair(0, false);
    }
    h0 = h1;
    h1 = h;
  }
  return make_pair(h1, true);
}

int main()
{
  int N;
  double A;
  scanf("%d %lf", &N, &A);

  double lo = 0.0, hi = 1e10;
  double ans = 1e10;
  for (int i = 0; i < 200; i++) {
    const double mid = (lo + hi)/2.0;
    const pair<double,bool> r = f(N, A, mid);
    if (r.second) {
      ans = min(ans, r.first);
      hi = mid;
    } else {
      lo = mid;
    }
  }
  printf("%.2f\n", ans);
  return 0;
}
