#include <cstdio>
#include <complex>
using namespace std;
typedef complex<double> P;

inline double cross(const P& a, const P& b) { return a.real()*b.imag() - b.real()*a.imag(); }
struct line/*{{{*/
{
  P a, b;
  line() {}
  line(const P& p, const P& q) : a(p), b(q) {}

  inline P intersection(const line& ln) const
  {
    // assert(intersects(ln))
    const P x = b - a;
    const P y = ln.b - ln.a;
    return a + x*(cross(y, ln.a - a))/cross(y, x);
  }
};/*}}}*/

P sector(const P& a, const P& b)
{
  const double x = abs(a), y = abs(b);
  return a/x*y + b/y*x;
}

int main()
{
  double ax, ay, bx, by, cx, cy, h;
  while (scanf("%lf %lf %lf %lf %lf %lf %lf", &ax, &ay, &bx, &by, &cx, &cy, &h) != EOF) {
    const P a(ax, ay), b(bx, by), c(cx, cy);
    const line l(c, c + sector(b-c, a-c));
    const line m(a, a + sector(c-a, b-a));
    const P p = l.intersection(m);
    printf("%.2f %.2f\n", p.real(), p.imag());
  }
  return 0;
}
