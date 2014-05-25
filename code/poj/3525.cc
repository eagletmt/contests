#include <cstdio>
#include <vector>
#include <complex>
using namespace std;
typedef complex<double> P;
static const double EPS = 1e-8;

inline double cross(const P& a, const P& b) { return a.real()*b.imag() - b.real()*a.imag(); }

struct line
{
  P a, b;
  line() {}
  line(const P& p, const P& q) : a(p), b(q) {}
};

struct segment
{
  P a, b;
  segment() {}
  segment(const P& x, const P& y) : a(x), b(y) {}

  inline double distance(const P& p) const
  {
    return abs(cross(p - a, b - a)) / abs(b - a);
  }

  inline bool intersects(const line& ln) const
  {
    return cross(ln.b - ln.a, a - ln.a) * cross(ln.b - ln.a, b - ln.a) < EPS;
  }

  inline P intersection(const line& ln) const
  {
    const P x = b - a;
    const P y = ln.b - ln.a;
    return a + x*(cross(y, ln.a - a))/cross(y, x);
  }

  inline bool parallel(const line& ln) const
  {
    return abs(cross(ln.b - ln.a, b - a)) < EPS;
  }
};

struct polygon
{
  vector<P> ps;
  polygon() {}
  polygon(const vector<P>& v) : ps(v) {}

  inline int size() const { return ps.size(); }
  inline void push_back(const P& p) { ps.push_back(p); }
  inline P& operator[](int i) { return ps[i]; }
  inline const P& operator[](int i) const { return ps[i]; }

  polygon cut(const line& ln) const
  {
    // cut out the left-side of the line
    const int N = ps.size();
    polygon ret;
    for (int i = 0; i < N; i++) {
      const segment seg(ps[i], ps[(i+1)%N]);
      if (cross(ln.b - ln.a, ps[i] - ln.a) < EPS) {
        // ps[i] is right-side of the line
        ret.push_back(ps[i]);
        if (!seg.parallel(ln) && seg.intersects(ln)) {
          const P p = seg.intersection(ln);
          if (abs(p - ps[i]) > EPS) {
            ret.push_back(p);
          }
        }
      } else if (!seg.parallel(ln) && seg.intersects(ln)) {
        ret.push_back(seg.intersection(ln));
      }
    }
    return ret;
  }
};

bool ok(const polygon& poly, double d)
{
  const int N = poly.size();
  polygon p = poly;
  for (int i = 0; i < N; i++) {
    P n = (poly[(i+1)%N] - poly[i]) * P(0, 1);
    n = n/abs(n) * d;
    p = p.cut(line(poly[(i+1)%N] + n, poly[i] + n));
  }
  return p.size() != 0;
}

int main()
{
  int N;
  while (scanf("%d", &N) != EOF && N != 0) {
    polygon poly;
    for (int i = 0; i < N; i++) {
      int x, y;
      scanf("%d %d", &x, &y);
      poly.push_back(P(x, y));
    }

    double left = 0.0, right = 100000;
    for (int i = 0; i < 100; i++) {
      const double mid = (left+right)/2.0;
      if (ok(poly, mid)) {
        left = mid;
      } else {
        right = mid;
      }
    }
    printf("%.6f\n", (left+right)/2.0);
  }
  return 0;
}
