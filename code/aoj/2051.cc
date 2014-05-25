#include <cstdio>
#include <vector>
#include <complex>
#include <cmath>
#include <algorithm>
using namespace std;
typedef complex<double> P;
static const double EPS = 1e-6;
static const double PI = acos(-1.0);
namespace std {
  bool operator<(const P& a, const P& b)
  {
    if (fabs(a.real() - b.real()) < EPS) {
      return a.imag() < b.imag() - EPS;
    } else {
      return a.real() < b.real() - EPS;
    }
  }
};
inline double dot(const P& a, const P& b) { return a.real()*b.real() + a.imag()*b.imag(); }

void move_to_origin(vector<P>& ps)
{
  P p(0, 0);
  for (vector<P>::const_iterator it = ps.begin(); it != ps.end(); ++it) {
    p += *it;
  }
  p /= ps.size();
  for (vector<P>::iterator it = ps.begin(); it != ps.end(); ++it) {
    *it -= p;
  }
}

vector<P> rot(const vector<P>& ps, double theta)
{
  const P p = polar(1.0, theta);
  vector<P> ans;
  for (vector<P>::const_iterator it = ps.begin(); it != ps.end(); ++it) {
    ans.push_back(*it * p);
  }
  sort(ans.begin(), ans.end());
  return ans;
}

bool equal(const vector<P>& ps, const vector<P>& qs)
{
  const int N = ps.size();
  for (int i = 0; i < N; i++) {
    if (abs(ps[i] - qs[i]) > EPS) {
      return false;
    }
  }
  return true;
}

int main()
{
  int N;
  while (scanf("%d", &N) != EOF && N != 0) {
    vector<P> ps, qs;
    for (int i = 0; i < N; i++) {
      double x, y;
      scanf("%lf %lf", &x, &y);
      ps.push_back(P(x, y));
    }
    for (int i = 0; i < N; i++) {
      double x, y;
      scanf("%lf %lf", &x, &y);
      qs.push_back(P(x, y));
    }

    move_to_origin(ps);
    move_to_origin(qs);
    sort(ps.begin(), ps.end());
    const double arg0 = fmod(arg(ps[0]) + 2*PI, 2*PI);
    double ans = 100;
    for (int i = 0; i < N; i++) {
      const double theta = arg0 - fmod(arg(qs[i]) + 2*PI, 2*PI);
      const vector<P> rs = rot(qs, theta);
      if (equal(ps, rs)) {
        const double t = fabs(theta);
        ans = min(ans, min(t, 2*PI-t));
      }
    }
    printf("%.7f\n", ans);
  }
  return 0;
}
