#include <cstdio>
#include <vector>
#include <queue>
#include <complex>
using namespace std;
typedef complex<double> P;
static const double EPS = 1e-6;
inline double cross(const P& a, const P& b) { return a.real()*b.imag() - b.real()*a.imag(); }

struct line/*{{{*/
{
  P a, b;
  line() {}
  line(const P& p, const P& q) : a(p), b(q) {}
};/*}}}*/

struct segment/*{{{*/
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
};/*}}}*/

int main()
{
  int N;
  while (scanf("%d", &N) != EOF && N != 0) {
    int vw, vc;
    scanf("%d %d", &vw, &vc);
    vector<P> ps;
    for (int i = 0; i < N; i++) {
      int x, y;
      scanf("%d %d", &x, &y);
      ps.push_back(P(x, y));
    }

    vector<vector<pair<int,double> > > g(3*N);
    for (int i = 0; i < N-1; i++) {
      g[3*i].push_back(make_pair(3*(i+1), abs(ps[i+1] - ps[i])/vw));
    }
    for (int i = 0; i < N; i++) {
      if (i > 0 && ps[i-1].imag() > ps[i].imag()) {
        // left edge
        const line ln(ps[i], ps[i] + P(1, 0));
        for (int j = i-2; j >= 0; j--) {
          const segment s(ps[j], ps[j+1]);
          if (s.intersects(ln)) {
            const P p = s.intersection(ln);
            const int n = 3*i+1;
            g[3*j].push_back(make_pair(n, abs(p - ps[j])/vw));
            g[n].push_back(make_pair(3*i, abs(ps[i] - p)/vc));
            break;
          }
        }
      }
      if (i < N-1 && ps[i].imag() < ps[i+1].imag()) {
        // right edge
        const line ln(ps[i], ps[i] + P(1, 0));
        for (int j = i+1; j < N-1; j++) {
          const segment s(ps[j], ps[j+1]);
          if (s.intersects(ln)) {
            const P p = s.intersection(ln);
            const int n = 3*i+2;
            g[3*i].push_back(make_pair(n, abs(p - ps[i])/vc));
            g[n].push_back(make_pair(3*(j+1), abs(ps[j+1] - p)/vw));
            break;
          }
        }
      }
    }

    static const double INF = 1e10;
    vector<double> dist(3*N, INF);
    dist[0] = 0;
    priority_queue<pair<double,int> > q;
    q.push(make_pair(0, 0));
    while (!q.empty()) {
      const double c = -q.top().first;
      const int n = q.top().second;
      q.pop();
      if (n == 3*(N-1)) {
        printf("%.6f\n", c);
        break;
      }
      if (c > dist[n]) {
        continue;
      }
      for (vector<pair<int,double> >::const_iterator it = g[n].begin(); it != g[n].end(); ++it) {
        const int m = it->first;
        const double cc = c + it->second;
        if (cc < dist[m]) {
          dist[m] = cc;
          q.push(make_pair(-cc, m));
        }
      }
    }
  }
  return 0;
}
