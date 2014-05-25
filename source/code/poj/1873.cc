#include <cstdio>
#include <algorithm>
#include <complex>
using namespace std;
typedef complex<double> P;
static const double EPS = 1e-6;
namespace std {
  bool operator<(const P& p, const P& q)
  {
    return abs(p.real() - q.real()) < EPS ? p.imag() < q.imag() : p.real() < q.real();
  }
};

inline double cross(const P& a, const P& b) { return a.real()*b.imag() - b.real()*a.imag(); }

double convex_len(const P *ps, int N)/* {{{*/
{
  static P ch[40];
  int k = 0;
  for (int i = 0; i < N; i++) {
    while (k >= 2 && cross(ch[k-1]-ch[k-2], ps[i]-ch[k-2]) <= EPS) {
      k--;
    }
    ch[k] = ps[i];
    k++;
  }
  for (int i = N-2, t = k+1; i >= 0; i--) {
    while (k >= t && cross(ch[k-1]-ch[k-2], ps[i]-ch[k-2]) <= EPS) {
      k--;
    }
    ch[k] = ps[i];
    k++;
  }
  const int K = k-1;
  double l = 0.0;
  for (int i = 0; i < K; i++) {
    l += abs(ch[i] - ch[(i+1)%K]);
  }
  return l;
}/*}}}*/

int main()
{
  int N;
  for (int Ti = 1; scanf("%d", &N) != EOF && N != 0; Ti++) {
    static P ps[20];
    static int vs[20], ls[20];
    for (int i = 0; i < N; i++) {
      int x, y;
      scanf("%d %d %d %d", &x, &y, &vs[i], &ls[i]);
      ps[i] = P(x, y);
    }

    int ans;
    int min_lost = 10000000;
    double extra;
    for (int s = 1; s < (1<<N); s++) {
      static P qs[20];
      int lost = 0, len = 0, size = 0;
      for (int i = 0; i < N; i++) {
        if (s & (1<<i)) {
          qs[size++] = ps[i];
        } else {
          len += ls[i];
          lost += vs[i];
        }
      }
      if (lost > min_lost) {
        continue;
      }
      sort(qs, qs+size);
      const double l = convex_len(qs, size);
      if (l <= len) {
        if (lost < min_lost || (lost == min_lost  && __builtin_popcount(~s) < __builtin_popcount(ans))) {
          min_lost = lost;
          ans = ~s;
          extra = len - l;
        }
      }
    }

    printf("Forest %d\n", Ti);
    printf("Cut these trees:");
    for (int i = 0; i < N; i++) {
      if (ans & (1<<i)) {
        printf(" %d", i+1);
      }
    }
    putchar('\n');
    printf("Extra wood: %.2f\n\n", extra);
  }
  return 0;
}
