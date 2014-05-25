#include <cstdio>
#include <vector>
#include <complex>
using namespace std;
typedef complex<double> P;

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
  inline P intersect(const segment& seg) const
  {
    const double d1 = seg.distance(a);
    const double d2 = seg.distance(b);
    const double t = d1 / (d1 + d2);
    return (1-t)*a + t*b;
  }
};
ostream& operator<<(ostream& os, const segment& seg)
{
  return os << seg.a << "-" << seg.b;
}

double area(const vector<P>& poly)
{
  double a = 0.0;
  const int N = poly.size();
  for (int i = 0; i < N; i++) {
    a += cross(poly[i], poly[(i+1)%N]);
  }
  return abs(a)/2.0;
}

int main()
{
  int N;
  while (scanf("%d", &N) != EOF && N != 0) {
    vector<double> ps[4];
    for (int i = 0; i < 4; i++) {
      ps[i].push_back(0.0);
      for (int j = 0; j < N; j++) {
        double x;
        scanf("%lf", &x);
        ps[i].push_back(x);
      }
      ps[i].push_back(1.0);
    }

    double ans = 0.0;
    for (int i = 0; i <= N; i++) {
      for (int j = 0; j <= N; j++) {
        const P a1(ps[0][i], 0.0), a2(ps[0][i+1], 0.0);
        const P b1(ps[1][i], 1.0), b2(ps[1][i+1], 1.0);
        const P c1(0.0, ps[2][j]), c2(0.0, ps[2][j+1]);
        const P d1(1.0, ps[3][j]), d2(1.0, ps[3][j+1]);
        const segment left(a1, b1), right(a2, b2);
        const segment bottom(c1, d1), top(c2, d2);
        vector<P> poly;
        poly.push_back(left.intersect(top));
        poly.push_back(right.intersect(top));
        poly.push_back(right.intersect(bottom));
        poly.push_back(left.intersect(bottom));
        ans = max(ans, area(poly));
      }
    }
    printf("%.6f\n", ans);
  }
  return 0;
}
