#include <cstdio>
#include <vector>
#include <set>
#include <cmath>
#include <complex>
#include <algorithm>
using namespace std;
typedef complex<double> P;
static const double EPS = 1e-6;

namespace std {
  bool operator<(const P& a, const P& b)
  {
    if (fabs(a.real() - b.real()) < EPS) {
      return a.imag() < b.imag();
    } else {
      return a.real() < b.real();
    }
  }
};

bool lattice(const P& p, pair<int,int>& pp)
{
  pp.first = lround(p.real());
  pp.second = lround(p.imag());
  return fabs(pp.first - p.real()) < EPS && fabs(pp.second - p.imag() < EPS);
}

int main()
{
  int N;
  while (scanf("%d", &N) != EOF && N != 0) {
    vector<P> v;
    set<pair<int,int> > s;
    for (int i = 0; i < N; i++) {
      int x, y;
      scanf("%d %d", &x, &y);
      v.push_back(P(x, y));
      s.insert(make_pair(x, y));
    }
    sort(v.begin(), v.end());

    int ans = 0;
    for (int i = 0; i < N; i++) {
      for (int j = i+1; j < N; j++) {
        const P d = (v[j] - v[i]) * P(0, 1);
        if (d.real() < 0 || d.imag() < 0) {
          continue;
        }
        const P p = v[i] + d;
        const P q = v[j] + d;
        pair<int,int> pp, qq;
        if (lattice(p, pp) && lattice(q, qq)
            && s.count(pp) && s.count(qq)) {
          ++ans;
        }
      }
    }
    printf("%d\n", ans);
  }
  return 0;
}
