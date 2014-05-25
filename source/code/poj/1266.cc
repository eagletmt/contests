#include <iostream>
#include <complex>
#include <cmath>
using namespace std;
typedef complex<double> P;

inline double cross(const P& a, const P& b)
{
  return a.real()*b.imag() - b.real()*a.imag();
}

struct line
{
  P a, b;
  line(const P& x, const P& y) : a(x), b(y) {}

  inline P intersection(const line& ln) const
  {
    const P x = b - a;
    const P y = ln.b - ln.a;
    return a + x*(cross(y, ln.a - a))/cross(y, x);
  }
};

P circle_center(const P& a, const P& b, const P& c)
{
  const P m = (a+b)/2.0;
  const P n = (b+c)/2.0;
  const P x = m + (b-a)*P(0,1);
  const P y = n + (c-b)*P(0,1);
  return line(m, x).intersection(line(n, y));
}

inline bool arc_intersects(const P& a, const P& b, const P& c, const P& p)
{
  return cross(b - a, c - a) * cross(b - a, p - a) > 0.0;
}

int main()
{
  P a, b, c;
  cin >> a.real() >> a.imag() >> b.real() >> b.imag() >> c.real() >> c.imag();

  const P o = circle_center(a, b, c);
  const double R = abs(a - o);
  const P left = o + P(-R, 0);
  const P right = o + P(R, 0);
  const P bottom = o + P(0, -R);
  const P top = o + P(0, R);

  const int x0 = floor(arc_intersects(a, b, c, left) ? left.real() : min(a.real(), b.real()));
  const int x1 = ceil(arc_intersects(a, b, c, right) ? right.real() : max(a.real(), b.real()));
  const int y0 = floor(arc_intersects(a, b, c, bottom) ? bottom.imag() : min(a.imag(), b.imag()));
  const int y1 = ceil(arc_intersects(a, b, c, top) ? top.imag() : max(a.imag(), b.imag()));
  cout << (x1 - x0)*(y1 - y0) << endl;
  return 0;
}
