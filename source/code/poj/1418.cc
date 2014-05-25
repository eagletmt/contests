#include <cstdio>
#include <vector>
#include <complex>
#include <algorithm>
#include <cmath>
using namespace std;
typedef complex<double> P;
static const double EPS = 1e-13;

inline double dot(const P& p, const P& q) { return p.real()*q.real() + p.imag()*q.imag(); }
inline double cross(const P& a, const P& b) { return a.real()*b.imag() - b.real()*a.imag(); }

struct line
{
  P a, b;
  line() {}
  line(const P& p, const P& q) : a(p), b(q) {}

  inline double distance(const P& p) const
  {
    return cross(b - a, p - a)/abs(b - a);
  }

  inline P perpendicular(const P& p) const
  {
    const double t = dot(p-a, a-b) / dot(b-a, b-a);
    return a + t*(a-b);
  }
};

struct circle
{
  P o;
  double r;
  circle() {}
  circle(const P& p, double x) : o(p), r(x) {}

  bool intersects(const circle& c) const
  {
    const double l = abs(o - c.o);
    return fabs(r - c.r) <= l && l <= r + c.r;
  }

  bool contains(const circle& c) const
  {
    return abs(o - c.o)+c.r <= r;
  }

  bool intersects(const line& ln) const
  {
    return abs(ln.distance(o)) <= r;
  }

  pair<P,P> intersection(const circle& c) const
  {
    // assert(intersects(c))
    const double d = abs(o - c.o);
    const double cos_ = (d*d + r*r - c.r*c.r) / (2*d);
    const double sin_ = sqrt(r*r - cos_*cos_);
    const P e = (c.o - o) / d;
    return make_pair(o + e*P(cos_, sin_), o + e*P(cos_, -sin_));
  }

  pair<P,P> intersection(const line& ln) const
  {
    const P h = ln.perpendicular(o);
    const double d = abs(h - o);
    P ab = ln.b - ln.a;
    ab /= abs(ab);
    const double l = sqrt(r*r - d*d);
    return make_pair(h + l*ab, h - l*ab);
  }
};

int main()
{
  int N;
  while (scanf("%d", &N) != EOF && N != 0) {
    vector<circle> cs;
    for (int i = 0; i < N; i++) {
      double x, y, r;
      scanf("%lf %lf %lf", &x, &y, &r);
      cs.push_back(circle(P(x, y), r));
    }
    vector<double> xs;
    vector<int> visible(N, true);
    for (int i = 0; i < N; i++) {
      xs.push_back(cs[i].o.real());
      xs.push_back(cs[i].o.real() - cs[i].r);
      xs.push_back(cs[i].o.real() + cs[i].r);
      for (int j = i+1; j < N; j++) {
        if (cs[i].intersects(cs[j])) {
          visible[i] = visible[j] = false;
          const pair<P,P> r = cs[i].intersection(cs[j]);
          xs.push_back(r.first.real());
          xs.push_back(r.second.real());
          xs.push_back((r.first.real() + r.second.real())/2.0);
        } else if (cs[j].contains(cs[i])) {
          visible[i] = false;
        }
      }
    }

    for (vector<double>::const_iterator it = xs.begin(); it != xs.end(); ++it) {
      const line ln(P(*it, 0), P(*it, 1));
      vector<pair<pair<double, double>, int> > v;
      for (int i = 0; i < N; i++) {
        if (cs[i].intersects(ln)) {
          const pair<P,P> r = cs[i].intersection(ln);
          double y1 = r.first.imag(), y2 = r.second.imag();
          if (y1 > y2) {
            swap(y1, y2);
          }
          // y1 <= y2
          if (y2 - y1 > EPS) {
            v.push_back(make_pair(make_pair(y1, y2), i));
          }
        }
      }
      for (vector<pair<pair<double, double>, int> >::const_iterator jt = v.begin(); jt != v.end(); ++jt) {
        if (visible[jt->second]) {
          continue;
        }
        double y1 = jt->first.first;
        double y2 = jt->first.second;
        for (vector<pair<pair<double, double>, int> >::const_iterator kt = v.begin(); kt != v.end(); ++kt) {
          const double yy1 = kt->first.first;
          const double yy2 = kt->first.second;
          if (jt->second < kt->second && yy1 < y2+EPS && y1 < yy2+EPS) {
            if (y2 < yy2 + EPS) {
              y2 = min(y2, yy1);
            }
            if (yy1 < y1 + EPS) {
              y1 = max(y1, yy2);
            }
          }
        }
        if (y2 - y1 > EPS) {
          visible[jt->second] = true;
        }
      }
    }
    printf("%ld\n", count(visible.begin(), visible.end(), true));
  }
  return 0;
}
