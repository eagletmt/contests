#include <cstdio>
#include <vector>
#include <algorithm>
#include <complex>
#include <cmath>
using namespace std;
typedef complex<double> P;
static const double EPS = 1e-6;
namespace std {
  bool operator<(const P& lhs, const P& rhs)
  {
    if (abs(lhs.real() - rhs.real()) < EPS) {
      return lhs.imag() < rhs.imag();
    } else {
      return lhs.real() < rhs.real();
    }
  }
};

inline double sqr(double x) { return x*x; }

int main()
{
  int Ti = 0;
  int n, d;
  while (scanf("%d %d", &n, &d) != EOF && n != 0) {
    vector<pair<double, P> > ps(n);
    bool ng = false;
    for (int i = 0; i < n; i++) {
      int x, y;
      scanf("%d %d", &x, &y);
      ps[i].second = P(x, y);
      ng = ng || abs(ps[i].second.imag()) > d;
      ps[i].first = ps[i].second.real() + sqrt(sqr(d) - sqr(ps[i].second.imag()));
    }
    int ans = 0;
    if (ng) {
      ans = -1;
    } else {
      sort(ps.begin(), ps.end());
      for (vector<pair<double,P> >::const_iterator it = ps.begin(); it != ps.end();) {
        ++ans;
        const P p(it->first, 0.0);
        while (it != ps.end() && abs(it->second - p) <= d + EPS) {
          ++it;
        }
      }
    }
    printf("Case %d: %d\n", ++Ti, ans);
  }
  return 0;
}
