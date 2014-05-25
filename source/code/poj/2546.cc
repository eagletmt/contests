#include <cstdio>
#include <complex>
#include <cmath>
using namespace std;
typedef complex<double> P;
static const double PI = atan2(+0.0, -0.0);
static const double EPS = 1e-6;

inline double cross(const P& a, const P& b)
{
  return a.real()*b.imag() - b.real()*a.imag();
}

struct segment
{
  P a, b;
  segment() {}
  segment(const P& x, const P& y) : a(x), b(y) {}
  inline double distance(const P& p) const
  {
    return abs(cross(p - a, b - a)) / abs(b - a);
  }
  inline double length() const { return abs(b - a); }
  inline P intersect(const segment& seg) const
  {
    const double d1 = seg.distance(a);
    const double d2 = seg.distance(b);
    const double t = d1 / (d1 + d2);
    return (1-t)*a + t*b;
  }
};

struct circle
{
  P o;
  double r;
  circle() {}
  circle(const P& o_, double r_) : o(o_), r(r_) {}

  inline double area() const { return PI*r*r; }
  double intersection_area(const circle& c) const
  {
    const double d = abs(c.o - o);
    //if (d > r + c.r) {
    if (r + c.r - d < EPS) {
      return 0.0;
    //} else if (d < abs(r - c.r)) {
    } else if (d - abs(r - c.r) < EPS) {
      const double r1 = min(r, c.r);
      return r1*r1*PI;
    } else {
      const double cos_ = (d*d + r*r - c.r*c.r) / (2*d);
      const double theta = acos(cos_ / r);
      const double phi = acos((d - cos_) / c.r);
      return r*r*theta + c.r*c.r*phi - d*r*sin(theta);
    }
  }
};

int main()
{
  double x1, y1, r1, x2, y2, r2;
  scanf("%lf %lf %lf %lf %lf %lf\n", &x1, &y1, &r1, &x2, &y2, &r2);
  const circle c1(P(x1, y1), r1), c2(P(x2, y2), r2);
  printf("%.3f\n", c1.intersection_area(c2));
  return 0;
}
