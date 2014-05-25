#include <cstdio>
#include <vector>
#include <map>
#include <cmath>
using namespace std;
static const double EPS = 1e-6;

struct P
{
  double x, y, z;
  P() {}
  P(double a, double b, double c) : x(a), y(b), z(c) {}
  P operator+(const P& that) const { return P(x + that.x, y + that.y, z + that.z); }
  P operator-(const P& that) const { return P(x - that.x, y - that.y, z - that.z); }
  P& operator*=(double a) { x *= a; y *= a; z *= a; return *this; }
  P operator*(double a) const { P p(*this); p *= a; return p; }
  P& operator/=(double a) { x /= a; y /= a; z /= a; return *this; }
  P operator/(double a) const { P p(*this); p /= a; return p; }

  double abs() const { return sqrt(x*x + y*y + z*z); }
  double dot(const P& that) const { return x*that.x + y*that.y + z*that.z; }
  P cross(const P& that) const
  {
    return P(
        y*that.z - that.y*z,
        z*that.x - that.z*x,
        x*that.y - that.x*y);
  }
};

struct line
{
  P a, b;
  line(const P& x, const P& y) : a(x), b(y) {}
};

struct sphere
{
  P o;
  double r;
  sphere(const P& p, double x) : o(p), r(x) {}

  bool intersects(const line& ln) const
  {
    const P ab = ln.b - ln.a;
    const P ao = o - ln.a;
    if (ab.dot(ao) < 0) {
      return false;
    }
    const double h = ab.cross(ao).abs() / ab.abs();
    return h < r;
  }

  P intersection(const line& ln) const
  {
    const P ab = ln.b - ln.a;
    const P ao = o - ln.a;
    const double h = ab.cross(ao).abs() / ab.abs();
    const double d = ao.abs();
    const double l = sqrt(d*d - h*h);
    double left = 0.0, right = l/ab.abs();
    for (int i = 0; i < 100; i++) {
      const double mid = (left + right)/2.0;
      const P ap = ab*mid;
      const double t = (ap - ao).abs();
      if (t < r) {
        right = mid;
      } else {
        left = mid;
      }
    }
    return ln.a + ab*((left + right)/2.0);
  }

  line reflect(const line& ln) const
  {
    const P q = intersection(ln);
    const P qa = ln.a - q;
    P qn = q - o;
    qn /= qn.abs();
    const P x = qn.cross(qa);
    if (x.abs() < EPS) {
      return line(q, ln.a);
    }
    P qm = qn.cross(x);
    qm /= qm.abs();
    const double t = qn.dot(qa)/(qn.abs()*qa.abs());
    const P qr = qm*sqrt(1-t*t) + qn*t;
    return line(q, q + qr);
  }
};

int main()
{
  int N;
  while (scanf("%d", &N) != EOF && N != 0) {
    int u, v, w;
    scanf("%d %d %d", &u, &v, &w);
    line ln(P(0, 0, 0), P(u, v, w));
    vector<sphere> ss;
    for (int i = 0; i < N; i++) {
      int x, y, z, r;
      scanf("%d %d %d %d", &x, &y, &z, &r);
      ss.push_back(sphere(P(x, y, z), r));
    }

    P ans;
    for (;;) {
      map<double,int> m;
      for (int i = 0; i < N; i++) {
        if (ss[i].intersects(ln)) {
          const P p = ss[i].intersection(ln);
          m.insert(make_pair((p - ln.a).abs(), i));
        }
      }
      if (m.empty()) {
        break;
      }
      const sphere& s = ss[m.begin()->second];
      ln = s.reflect(ln);
      ans = ln.a;
    }
    printf("%.4f %.4f %.4f\n", ans.x, ans.y, ans.z);
  }
  return 0;
}
