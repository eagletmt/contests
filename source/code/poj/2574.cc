#include <cstdio>
#include <algorithm>
#include <complex>
#include <cmath>
using namespace std;
typedef complex<int> PL;
typedef complex<double> P;

inline long long ABS(long long x) { return x < 0 ? -x : x; }
inline long long cross(const PL& a, const PL& b) { return static_cast<long long>(a.real())*b.imag() - static_cast<long long>(b.real())*a.imag(); }

struct line/*{{{*/
{
  PL a, b;
  line() {}
  line(const PL& p, const PL& q) : a(p), b(q) {}
};/*}}}*/

struct segment/*{{{*/
{
  PL a, b;
  PL pa, pb;
  segment() {}
  segment(const PL& x, const PL& y) : a(x), b(y) {}

  inline int intersects(const line& ln) const
  {
    long long x = cross(ln.b - ln.a, a - ln.a);
    long long y = cross(ln.b - ln.a, b - ln.a);
    if (x == 0 && y == 0) {
      return 0;
    } else if (x == 0) {
      return 1;
    } else if (y == 0) {
      return 2;
    } else if ((x/ABS(x)) * (y/ABS(y)) < 0) {
      return 3;
    } else {
      return 4;
    }
  }

  inline P intersection(const line& ln) const
  {
    // assert(intersects(ln))
    const PL x = b - a;
    const PL y = ln.b - ln.a;
    const P xx(x.real(), x.imag());
    const P aa(a.real(), a.imag());
    return aa + xx*double(cross(y, ln.a - a))/double(cross(y, x));
  }
};/*}}}*/

struct by_y
{
  bool operator()(const segment& l, const segment& r) const
  {
    int a = min(l.a.imag(), l.b.imag());
    int b = min(r.a.imag(), r.b.imag());
    if (a == b) {
      return max(l.a.imag(), l.b.imag()) < max(r.a.imag(), r.b.imag());
    } else {
      return a < b;
    }
  }
};

int main()
{
  static PL polygon[100];
  int left = 1000000, right = 0;
  int N = 0;
  for (int x, y; scanf("%d %d", &x, &y) != EOF;) {
    polygon[N++] = PL(x, y);
    left = min(left, x);
    right = max(right, x);
  }
  static segment ss[100];
  for (int i = 0; i < N; i++) {
    ss[i].a = polygon[i];
    ss[i].b = polygon[(i+1)%N];
  }
  for (int i = 0; i < N; i++) {
    ss[i].pa = ss[(i-1+N)%N].a;
    ss[i].pb = ss[(i-1+N)%N].a;
  }
  sort(ss, ss+N, by_y());

  long long ans = 0;
  static int ys[2][100];
  int M[2] = {0, 0};
  for (int x = left, cnt = 0; x <= right; x++, cnt ^= 1) {
    const line ln(PL(x, -2), PL(x, -1));
    int *p = ys[cnt];
    int& n = M[cnt];
    n = 0;
    for (int i = 0; i < N; i++) {
      switch (ss[i].intersects(ln)) {
        case 0:
          {
            if (n % 2 == 1) {
              int y1 = ss[i].a.imag(), y2 = ss[i].b.imag();
              if (y1 > y2) {
                swap(y1, y2);
              }
              p[n++] = y1;
              p[n++] = y1;
              p[n++] = y2;
            } else {
              int r = segment(ss[i].b, ss[i].pa).intersects(line(ln));
              if (r != 4) {
                p[n++] = ss[i].a.imag();
              }
            }
          }
          break;
        case 1:
          {
            int r = segment(ss[i].b, ss[i].pa).intersects(line(ln));
            if (r != 4) {
              p[n++] = ss[i].a.imag();
            }
          }
          break;
        case 2:
          break;
        case 3:
          {
            double y = ss[i].intersection(ln).imag();
            if (n % 2 == 0) {
              p[n++] = ceil(y);
            } else {
              p[n++] = floor(y);
            }
          }
          break;
        case 4:
          break;
      }
    }
    const int *q = ys[cnt ^ 1];
    const int m = M[cnt ^ 1];
    for (int i = 0, j = 0; i < n && j < m;) {
      int beg1 = p[i], end1 = p[i+1];
      int beg2 = q[j], end2 = q[j+1];
      if (end1 <= beg2) {
        i += 2;
      } else if (end2 <= beg1) {
        j += 2;
      } else if (end1 <= end2) {
        ans += static_cast<long long>(end1 - max(beg1, beg2));
        i += 2;
      } else {
        ans += static_cast<long long>(end2 - max(beg1, beg2));
        j += 2;
      }
    }
  }
  printf("%lld\n", ans);
  return 0;
}
