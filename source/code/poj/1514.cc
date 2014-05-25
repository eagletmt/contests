#include <cstdio>
#include <algorithm>
#include <complex>
using namespace std;
typedef complex<double> P;
static const double EPS = 1e-6;

inline double cross(const P& a, const P& b)
{
  return a.real()*b.imag() - b.real()*a.imag();
}

struct line
{
  P a, b;
  line() {}
  line(const P& x, const P& y) : a(x), b(y) {}

  inline bool parallel(const line& ln) const
  {
    return abs(cross(ln.b - ln.a, b - a)) < EPS;
  }

  inline bool intersects(const line& ln) const
  {
    return !parallel(ln);
  }

  inline P intersection(const line& ln) const
  {
    const P x = b - a;
    const P y = ln.b - ln.a;
    return a + x*(cross(y, ln.a - a))/cross(y, x);
  }
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

  inline bool parallel(const line& ln) const
  {
    return abs(cross(ln.b - ln.a, b - a)) < EPS;
  }
};

struct polygon
{
  P ps[16];
  int N;
  polygon() : N(0) {}

  inline int size() const { return N; }
  inline void push_back(const P& p) { ps[N++] = p; }
  inline P& operator[](int i) { return ps[i]; }
  inline const P& operator[](int i) const { return ps[i]; }

  pair<polygon,double> cut(const line& ln) const
  {
    // cut out the left-side of the line
    polygon ret;
    P crosspoint[2];
    int cp = 0;
    for (int i = 0; i < N; i++) {
      const segment seg(ps[i], ps[(i+1)%N]);
      if (cross(ln.b - ln.a, ps[i] - ln.a) < EPS) {
        // ps[i] is right-side of the line
        ret.push_back(ps[i]);
        if (!seg.parallel(ln) && seg.intersects(ln)) {
          const P p = seg.intersection(ln);
          if (abs(p - ps[i]) > EPS) {
            ret.push_back(p);
            crosspoint[cp++] = p;
          }
        }
      } else if (!seg.parallel(ln) && seg.intersects(ln)) {
        const P p = seg.intersection(ln);
        ret.push_back(p);
        crosspoint[cp++] = p;
      }
    }
    if (cp == 2) {
      return make_pair(ret, abs(crosspoint[1] - crosspoint[0]));
    } else {
      throw "???";
    }
  }
};

int main()
{
  int n, m;
  scanf("%d %d", &n, &m);
  int p;
  scanf("%d", &p);
  P ps[8];
  for (int i = 0; i < p; i++) {
    int x, y;
    scanf("%d %d", &x, &y);
    ps[i] = P(x, y);
  }
  line ls[8];
  int a[8];
  for (int i = 0; i < p; i++) {
    ls[i] = line(ps[i], ps[(i+1)%p]);
    a[i] = i;
  }

  double ans = 1e9;
  do {
    polygon poly;
    poly.push_back(P(0, 0));
    poly.push_back(P(0, m));
    poly.push_back(P(n, m));
    poly.push_back(P(n, 0));
    double len = 0.0;
    for (int i = 0; i < p; i++) {
      const pair<polygon,double> r = poly.cut(ls[a[i]]);
      len += r.second;
      poly = r.first;
    }
    ans = min(ans, len);
  } while (next_permutation(a, a+p));
  printf("Minimum total length = %.3f\n", ans);
  return 0;
}
