#include <cstdio>
#include <vector>
#include <complex>
using namespace std;
typedef complex<double> P;
static const double EPS = 1e-6;

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
};

double area(const vector<segment> *ps, double h)
{
  double s = 0.0;
  const line ln(P(0, h), P(1, h));
  for (int i = 0; i < 2; i++) {
    for (vector<segment>::const_iterator it = ps[i].begin(); it != ps[i].end(); ++it) {
      P a = it->a, b = it->b;
      if (a.imag() < b.imag()) {
        swap(a, b);
      }

      if (a.imag() <= h) {
        s += (h - a.imag() + h - b.imag()) * fabs(a.real() - b.real()) / 2.0;
      } else if (it->intersects(ln)) {
        const P p = it->intersection(ln);
        s += fabs(p.real() - b.real()) * (p.imag() - b.imag()) / 2.0;
      }
    }
  }
  return s;
}

int main()
{
  int T;
  scanf("%d", &T);
  while (T-- > 0) {
    int A;
    scanf("%d", &A);
    vector<segment> ps[2];
    double left = 1e10;
    for (int i = 0; i < 2; i++) {
      int k;
      scanf("%d", &k);
      P prev;
      for (int j = 0; j < k; j++) {
        int x, y;
        scanf("%d %d", &x, &y);
        left = min(left, double(y));
        if (j != 0) {
          ps[i].push_back(segment(prev, P(x, y)));
        }
        prev = P(x, y);
      }
    }
    double right = min(min(ps[0].front().a.imag(), ps[0].back().b.imag()), min(ps[1].front().a.imag(), ps[1].back().b.imag()));
    for (int i = 0; i < 100; i++) {
      const double mid = (left + right)/2.0;
      const double s = area(ps, mid);
      if (s < A) {
        left = mid;
      } else {
        right = mid;
      }
    }
    printf("%.3f\n", (left + right)/2.0);
  }
  return 0;
}
