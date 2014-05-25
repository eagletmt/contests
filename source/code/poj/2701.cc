#include <cstdio>
#include <vector>
#include <cmath>
#include <complex>
#include <algorithm>
using namespace std;
typedef complex<double> P;
static const double EPS = 1e-6;

inline double dot(const P& a, const P& b) { return a.real()*b.real() + a.imag()*b.imag(); }
inline double cross(const P& a, const P& b) { return a.real()*b.imag() - b.real()*a.imag(); }

int ccw(const P& a, P b, P c)/*{{{*/
{
  b -= a;
  c -= a;
  if (cross(b, c) > EPS) {
    return +1;
  } else if (cross(b, c) < -EPS) {
    return -1;
  } else if (dot(b, c) < -EPS) {
    return +2;
  } else if (dot(b, b) + EPS < dot(c, c)) {
    return -2;
  } else {
    return 0;
  }
}/*}}}*/

struct segment/*{{{*/
{
  P a, b;
  segment() {}
  segment(const P& x, const P& y) : a(x), b(y) {}

  // AOJ 2402 Milkey Way
  inline bool intersects(const segment& seg) const
  {
    return ccw(a, b, seg.a) * ccw(a, b, seg.b) <= 0
      && ccw(seg.a, seg.b, a) * ccw(seg.a, seg.b, b) <= 0;
  }

  // AOJ 2402 Milkey Way
  inline double distance(const P& p) const
  {
    if (dot(b-a, p-a) < EPS) {
      return abs(p-a);
    } else if (dot(a-b, p-b) < EPS) {
      return abs(p-b);
    } else {
      return abs(cross(b-a, p-a))/abs(b-a);
    }
  }

  // AOJ 2402 Milkey Way
  inline double distance(const segment& seg) const
  {
    if (intersects(seg)) {
      return 0;
    } else {
      return
        min(
            min(distance(seg.a), distance(seg.b)),
            min(seg.distance(a), seg.distance(b)));
    }
  }
};/*}}}*/

struct polygon/*{{{*/
{
  vector<P> ps;
  polygon() {}
  polygon(const vector<P>& v) : ps(v) {}

  inline int size() const { return ps.size(); }
  inline void push_back(const P& p) { ps.push_back(p); }
  inline P& operator[](int i) { return ps[i]; }
  inline const P& operator[](int i) const { return ps[i]; }

  double distance(const segment& seg) const
  {
    const int N = size();
    double ans = 1e10;
    for (int i = 0; i < N; i++) {
      ans = min(ans, seg.distance(segment(ps[i], ps[(i+1)%N])));
    }
    return ans;
  }
};/*}}}*/

int main()
{
  double R0, R1;
  int N;
  while (scanf("%lf %lf %d", &R0, &R1, &N) != EOF && N != 0) {
    vector<polygon> v;
    for (int i = 0; i < N; i++) {
      int M;
      scanf("%d", &M);
      polygon p;
      for (int j = 0; j < M; j++) {
        double x, y;
        scanf("%lf %lf", &x, &y);
        p.push_back(P(x, y));
      }
      v.push_back(p);
    }
    int M;
    scanf("%d", &M);
    vector<P> path;
    for (int i = 0; i < M; i++) {
      double x, y;
      scanf("%lf %lf", &x, &y);
      path.push_back(P(x, y));
    }

    for (int i = 0; i < M-1; i++) {
      const segment seg(path[i], path[i+1]);
      double d = R1;
      for (vector<polygon>::const_iterator it = v.begin(); it != v.end(); ++it) {
        d = min(d, it->distance(seg));
      }
      if (i != 0) {
        putchar(' ');
      }
      if (d < R0) {
        putchar('0');
      } else {
        printf("%ld", lround(d));
      }
    }
    putchar('\n');
  }
  return 0;
}
