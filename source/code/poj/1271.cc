#include <cstdio>
#include <algorithm>
#include <complex>
using namespace std;
typedef complex<double> P;
static const double EPS = 1e-6;

inline double dot(const P& a, const P& b)
{
  return a.real()*b.real() + a.imag()*b.imag();
}

inline double cross(const P& a, const P& b)
{
  return a.real()*b.imag() - b.real()*a.imag();
}

struct line
{
  P base, dir;
  line() {}
  line(const P& x, const P& y) : base(x), dir(y - x) {}
};

struct segment
{
  P a, b;
  segment() {}
  segment(const P& x, const P& y) : a(x), b(y) {}

  inline bool intersects(const line& ln) const
  {
    return cross(ln.dir, a - ln.base) * cross(ln.dir, b - ln.base) < EPS;
  }

  inline P intersection(const line& ln) const
  {
    const P x = b - a;
    return a + x*(cross(ln.dir, ln.base - a))/cross(ln.dir, x);
  }

  inline bool parallel(const line& ln) const
  {
    return abs(cross(ln.dir, b - a)) < EPS;
  }
};

struct polygon
{
  int N;
  P ps[25];
  polygon() : N(0) {}

  inline int size() const { return N; }
  inline void push_back(const P& p) { ps[N++] = p; }
  inline P& operator[](int i) { return ps[i]; }
  inline const P& operator[](int i) const { return ps[i]; }

  double area() const
  {
    // positive if polygon is clockwise
    double a = 0.0;
    for (int i = 0; i < N; i++) {
      a += cross(ps[(i+1)%N], ps[i]);
    }
    return a/2.0;
  }

  polygon cut(const line& ln) const
  {
    // cut out the left-side of the line
    polygon ret;
    segment seg;
    for (int i = 0; i < N; i++) {
      seg.a = ps[i];
      seg.b = ps[(i+1)%N];
      if (cross(ln.dir, ps[i] - ln.base) < EPS) {
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

double dfs(const line *ls, int N, const polygon& poly, int i, int depth)
{
  if (depth == 0) {
    return poly.area();
  } else {
    double ans = poly.area();
    for (int j = i+1; j < N; j++) {
      ans = min(ans, dfs(ls, N, poly.cut(ls[j]), j, depth-1));
    }
    return ans;
  }
}

int main()
{
  int N, K, H;
  while (scanf("%d %d %d", &N, &K, &H) != EOF && N != 0) {
    K = min(K, N);
    polygon poly;
    for (int i = 0; i < N; i++) {
      int x, y;
      scanf("%d %d", &x, &y);
      poly.push_back(P(x, y));
    }
    if (K == 0 || H == 0) {
      puts("0.00");
      continue;
    }
    reverse(poly.ps, poly.ps + N);

    static line ls[20];
    for (int i = 0; i < N; i++) {
      const P& p1 = poly[i];
      const P& p2 = poly[(i+1)%N];
      const P dir = p2 - p1;
      const P n = dir*P(0.0, -1.0);
      const P h = H/abs(n)*n + p1;
      ls[i] = line(h, h + dir);
    }
    printf("%.2f\n", poly.area() - dfs(ls, N, poly, -1, K));
  }
  return 0;
}
