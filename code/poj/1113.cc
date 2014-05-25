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
  bool operator<(const P& p, const P& q)
  {
    return abs(p.real() - q.real()) < EPS ? p.imag() < q.imag() : p.real() < q.real();
  }
};

inline double dot(const P& a, const P& b)
{
  return a.real()*b.real() + a.imag()*b.imag();
}

inline double cross(const P& a, const P& b)
{
  return a.real()*b.imag() - b.real()*a.imag();
}

inline int ccw(P a, P b, P c) {/*{{{*/
  b -= a; c -= a;
  if (cross(b, c) > 0) {
    return 1; // counter clockwise
  } else if (cross(b, c) < 0) {
    return -1;  // clockwise
  } else if (dot(b, c) < 0) {
    return 2; // c-a-b on line
  } else if (abs(b) < abs(c)) {
    return -2;  // a-b-c on line
  }
  return 0;
}/*}}}*/

vector<P> convex(const vector<P>& ps)/*{{{*/
{
  const int N = ps.size();
  vector<P> ch(2*N);
  int k = 0;
  // upper
  for (int i = 0; i < N; i++) {
    while (k >= 2 && ccw(ch[k-2], ch[k-1], ps[i]) <= 0) {
      k--;
    }
    ch[k] = ps[i];
    k++;
  }
  // lower
  for (int i = N-2, t = k+1; i >= 0; i--) {
    while (k >= t && ccw(ch[k-2], ch[k-1], ps[i]) <= 0) {
      k--;
    }
    ch[k] = ps[i];
    k++;
  }
  ch.resize(k-1);
  return ch;
}/*}}}*/

int main()
{
  int N, L;
  scanf("%d %d", &N, &L);
  vector<P> ps;
  for (int i = 0; i < N; i++) {
    double x, y;
    scanf("%lf %lf", &x, &y);
    ps.push_back(P(x, y));
  }
  sort(ps.begin(), ps.end());

  const vector<P> qs = convex(ps);
  const int M = qs.size();
  double ans = 2*L*PI;
  for (int i = 0; i < M; i++) {
    ans += abs(qs[(i+1)%M] - qs[i]);
  }
  printf("%ld\n", lround(ans));

  return 0;
}
