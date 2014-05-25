#include <cstdio>
#include <vector>
#include <algorithm>
#include <complex>
#include <cmath>
using namespace std;
typedef complex<double> P;
static const double EPS = 1e-6;

inline double cross(const P& a, const P& b) { return a.real()*b.imag() - b.real()*a.imag(); }

struct line
{
  P a, b;
  line() {}
  line(const P& p, const P& q) : a(p), b(q) {}

  inline P intersection(const line& ln) const
  {
    const P x = b - a;
    const P y = ln.b - ln.a;
    return a + x*(cross(y, ln.a - a))/cross(y, x);
  }
};

struct circle
{
  P o;
  double r;
  circle() {}
  circle(const P& p, double x) : o(p), r(x) {}

  pair<P,P> tangent(const P& p) const
  {
    const double L = abs(o - p);
    const double M = sqrt(L*L - r*r);
    const double theta = asin(r / L);
    const P v = (o - p) / L;
    return make_pair(p + M*(v*polar(1.0, theta)), p + M*(v*polar(1.0, -theta)));
  }
};

int main()
{
  int N;
  while (scanf("%d", &N) != EOF && N != 0) {
    int bx, by;
    scanf("%d %d", &bx, &by);
    const P o(bx, by);
    const line base(P(0, 0), P(1, 0));
    vector<pair<double,double> > intervals(N);
    for (int i = 0; i < N; i++) {
      int x, y, r;
      scanf("%d %d %d", &x, &y, &r);
      const pair<P,P> ps = circle(P(x, y), r).tangent(o);
      intervals[i] = make_pair(
          base.intersection(line(o, ps.first)).real(),
          base.intersection(line(o, ps.second)).real());
      if (intervals[i].first > intervals[i].second) {
        swap(intervals[i].first, intervals[i].second);
      }
    }

    sort(intervals.begin(), intervals.end());
    pair<double,double> r = intervals[0];
    for (int i = 1; i < N; i++) {
      if (r.second + EPS > intervals[i].first) {
        r.second = max(r.second, intervals[i].second);
      } else {
        printf("%.2f %.2f\n", r.first, r.second);
        r = intervals[i];
      }
    }
    printf("%.2f %.2f\n\n", r.first, r.second);
  }
  return 0;
}
