#include <cstdio>
#include <complex>
#include <cmath>
using namespace std;
typedef complex<double> P;

inline double cross(const P& a, const P& b)
{
  return a.real()*b.imag() - b.real()*a.imag();
}

struct segment
{
  P a, b;
  segment(const P& x, const P& y) : a(x), b(y) {}
  inline P intersection(const segment& s) const
  {
    const P x = b - a;
    const P y = s.b - s.a;
    return a + x*(cross(y, s.a - a))/cross(y, x);
  }
};

int main()
{
  double x, y, c;
  while (scanf("%lf %lf %lf", &x, &y, &c) != EOF) {
    double left = 0.0, right = min(x, y);
    for (int i = 0; i < 100; i++) {
      const double w = (left + right) / 2.0;
      const segment s1(P(0.0, sqrt(x*x - w*w)), P(w, 0.0));
      const segment s2(P(0.0, 0.0), P(w, sqrt(y*y - w*w)));
      const P p = s1.intersection(s2);
      if (p.imag() < c) {
        right = w;
      } else {
        left = w;
      }
    }
    printf("%.3f\n", (right + left)/2.0);
  }
  return 0;
}
