#include <cstdio>
#include <cmath>
using namespace std;

int main()
{
  int N;
  for (int Ti = 1; scanf("%d", &N) != EOF && N != -1; Ti++) {
    double c[16];
    for (int i = 0; i <16; i++) {
      c[i] = 0.0;
    }
    for (int i = 0; i < N; i++) {
      int mon;
      double x;
      scanf("%d %lf", &mon, &x);
      c[mon] = x;
    }
    int lastmon;
    double amount;
    scanf("%d %lf", &lastmon, &amount);
    double lo = 0.0, hi = 1.0;
    for (int i = 0; i < 100; i++) {
      const double mid = (lo + hi)/2.0;
      double x = 0.0;
      for (int j = 1; j <= lastmon; j++) {
        x += c[j] * pow(mid+1, double(lastmon-j+1));
      }
      if (x < amount) {
        lo = mid;
      } else {
        hi = mid;
      }
    }
    printf("Case %d: %.5f\n\n", Ti, (lo+hi)/2.0);
  }
  return 0;
}
