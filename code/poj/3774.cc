#include <cstdio>
#include <vector>
#include <complex>
#include <cmath>
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

  inline P intersection(const segment& seg) const
  {
    // assert(intersects(seg))
    const P x = b - a;
    const P y = seg.b - seg.a;
    return a + x*(cross(y, seg.a - a))/cross(y, x);
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

  bool intersects(const segment& seg) const
  {
    const int N = size();
    for (int i = 0; i < N; i++) {
      if (seg.intersects(segment(ps[i], ps[(i+1)%N]))) {
        return true;
      }
    }
    return false;
  }

  P intersection_halfline(const segment& seg) const
  {
    // assert(intersects(seg));
    const int N = size();
    double len = 1e10;
    P p;
    for (int i = 0; i < N; i++) {
      const segment side(ps[i], ps[(i+1)%N]);
      if (seg.intersects(side)) {
        const P tmp = seg.intersection(side);
        const double d = abs(seg.a - tmp);
        if (d < len) {
          len = d;
          p = tmp;
        }
      }
    }
    return p;
  }
};/*}}}*/

P read()
{
  int x, y;
  scanf("%d %d", &x, &y);
  return P(x, y);
}

bool hits(const P& o, const P& dir, const vector<polygon>& v)
{
  const int N = v.size();
  const polygon target = v[0];
  const segment half(o,  o + (dir/abs(dir))*1e7);
  if (!target.intersects(half)) {
    return false;
  }
  const segment seg(o, target.intersection_halfline(half));

  for (int i = 1; i < N; i++) {
    if (v[i].intersects(seg)) {
      return false;
    }
  }
  return true;
}

int main()
{
  int N;
  while (scanf("%d", &N) != EOF && N != 0) {
    const P o = read();
    const P dir = read();
    vector<polygon> v;
    for (int i = 0; i < N; i++) {
      polygon p;
      int M;
      scanf("%d", &M);
      for (int j = 0; j < M; j++) {
        p.push_back(read());
      }
      v.push_back(p);
    }
    puts(hits(o, dir, v) ? "HIT" : "MISS");
  }
  return 0;
}
