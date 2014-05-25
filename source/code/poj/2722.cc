#include <cstdio>
#include <cmath>
using namespace std;

inline double sqr(double x) { return x*x; }

int main()
{
  int N;
  while (scanf("%d", &N) != EOF && N != 0) {
    double xa, ya, xb, yb;
    scanf("%lf %lf %lf %lf", &xa, &ya, &xb, &yb);
    const double a = ya/xa;
    const double b = yb/xb;
    double l = 0.0;
    double s = 0.0;
    for (int i = 0; i < N; i++) {
      double x;
      scanf("%lf", &x);
      l += x;
      s += x*x/2.0;
    }

    double left = 0.0, right = 1e10;
    for (int i = 0; i < 100; i++) {
      const double c = (left+right)/2.0;
      const double t = fabs(c/(a+1) - c/(b+1));
      if (t < l) {
        left = c;
      } else {
        right = c;
      }
    }
    const double c = (left+right)/2.0;
    printf("%.3f\n", c*c*fabs(b-a)/(2.0*(a+1)*(b+1)) - s);
  }
  return 0;
}
