#include <cstdio>
#include <iostream>
#include <vector>
#include <complex>
#include <limits>
using namespace std;
typedef complex<double> P;
static const double EPS = 1e-6;

inline bool feq(double x, double y) { return abs(x - y) < EPS; }
inline bool fleq(double x, double y) { return x <= y + EPS; }
inline double cross(const P& a, const P& b) { return a.real()*b.imag() - b.real()*a.imag(); }

struct line
{
  P a, b;
  line(const P& x, const P& y) : a(x), b(y) {}
};

struct segment
{
  P a, b;
  segment(const P& x, const P& y) : a(x), b(y) {}
  inline bool intersects(const line& ln) const
  {
    return cross(ln.b-ln.a, a-ln.a) * cross(ln.b-ln.a, b-ln.a) < EPS;
  }

  inline P intersection(const line& ln) const
  {
    const P x = b - a;
    const P y = ln.b - ln.a;
    return a + x*(cross(y, ln.a-a)/cross(y, x));
  }
};

int last_index(const vector<pair<P,P> >& v, const P& left, const P& right)
{
  const int N = v.size();
  const P e = (right - left) / abs(right - left);
  for (int i = 0; i < N; i++) {
    const double scale = (v[i].first.real() - left.real()) / e.real();
    P p = left + scale*e;
    if (!fleq(v[i].second.imag(), p.imag()) || !fleq(p.imag(), v[i].first.imag())) {
      return i-1;
    }
  }
  return N-1;
}

double update(double ans, const P& left, const P& right, const pair<P,P>& beg, const pair<P,P>& end)
{
  const line ln(left, right);
  const segment s1(beg.first, end.first);
  const segment s2(beg.second, end.second);
  if (s1.intersects(ln)) {
    ans = max(ans, s1.intersection(ln).real());
  }
  if (s2.intersects(ln)) {
    ans = max(ans, s2.intersection(ln).real());
  }
  return ans;
}

int main()
{
  int N;
  while (scanf("%d", &N) != EOF && N != 0) {
    vector<pair<P,P> > v(N);
    for (int i = 0; i < N; i++) {
      double x, y;
      scanf("%lf %lf", &x, &y);
      v[i] = make_pair(P(x, y), P(x, y-1));
    }

    double ans = -numeric_limits<double>::max();
    for (int i = 0; i < N; i++) {
      for (int j = i+1; j < N; j++) {
        const int k = last_index(v, v[i].first, v[j].second);
        const int l = last_index(v, v[i].second, v[j].first);
        if (max(k, l) == N-1) {
          puts("Through all the pipe.");
          goto NEXT;
        } else {
          if (j <= k) {
            ans = update(ans, v[i].first, v[j].second, v[k], v[k+1]);
          }
          if (j <= l) {
            ans = update(ans, v[i].second, v[j].first, v[l], v[l+1]);
          }
        }
      }
    }
    printf("%.2f\n", ans);
NEXT:
    ;
  }
  return 0;
}
