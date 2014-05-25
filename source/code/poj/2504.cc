#include <cstdio>
#include <iostream>
#include <vector>
#include <complex>
using namespace std;
typedef complex<double> P;
static const double EPS = 1e-6;
static const double PI = acos(-1.0);

inline double dot(const P& a, const P& b) { return a.real()*b.real() + a.imag()*b.imag(); }
inline double cross(const P& a, const P& b) { return a.real()*b.imag() - b.real()*a.imag(); }
struct line/*{{{*/
{
  P a, b;
  line() {}
  line(const P& p, const P& q) : a(p), b(q) {}

  inline bool parallel(const line& ln) const
  {
    return abs(cross(ln.b - ln.a, b - a)) < EPS;
  }

  inline bool intersects(const line& ln) const
  {
    return !parallel(ln);
  }

  inline P intersection(const line& ln) const
  {
    // assert(intersects(ln))
    const P x = b - a;
    const P y = ln.b - ln.a;
    return a + x*(cross(y, ln.a - a))/cross(y, x);
  }

  inline double distance(const P& p) const
  {
    return abs(cross(p - a, b - a)) / abs(b - a);
  }

  inline P perpendicular(const P& p) const
  {
    const double t = dot(p-a, a-b) / dot(b-a, b-a);
    return a + t*(a-b);
  }
};/*}}}*/

int main()
{
  int N;
  for (int Ti = 1; scanf("%d", &N) != EOF && N != 0; Ti++) {
    P ps[3];
    for (int i = 0; i < 3; i++) {
      double x, y;
      scanf("%lf %lf", &x, &y);
      ps[i] = P(x, y);
    }
    const P a = (ps[0] + ps[1])/2.0;
    const P aa = (ps[0] - a) * P(0, 1);
    const line aaa(a, a+aa);
    const P c = (ps[2] + ps[1])/2.0;
    const P cc = (ps[2] - c) * P(0, 1);
    const line ccc(c, c+cc);
    const P o = aaa.intersection(ccc);
    const double R = abs(ps[0] - o);

    double t = ps[0].imag(), b = ps[0].imag(), l = ps[0].real(), r = ps[0].real();
    double theta = arg(ps[0] - o);
    const double step = 2*PI/N;
    for (int i = 0; i < N; i++) {
      theta += step;
      const P p = polar(R, theta) + o;
      t = max(t, p.imag());
      b = min(b, p.imag());
      l = min(l, p.real());
      r = max(r, p.real());
    }
    printf("Polygon %d: %.3f\n", Ti, (t-b)*(r-l));
  }
  return 0;
}
