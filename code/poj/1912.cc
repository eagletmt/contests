#include <cstdio>
#include <complex>
#include <algorithm>
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

int main()
{
  int N;
  scanf("%d", &N);
  static P hs[100000];
  for (int i = 0; i < N; i++) {
    double x, y;
    scanf("%lf %lf", &x, &y);
    hs[i] = P(x, y);
  }
  sort(hs, hs+N);
  static P ls[100000], us[100000];
  int K1 = 0;
  for (int i = 0; i < N; i++) {
    while (K1 >= 2 && cross(ls[K1-2]-hs[i], ls[K1-1]-hs[i]) <= 0) {
      K1--;
    }
    ls[K1++] = hs[i];
  }
  int K2 = 0;
  us[K2++] = ls[K1-1];
  for (int i = N-2; i >= 0; i--) {
    while (K2 >= 2 && cross(us[K2-2]-hs[i], us[K2-1]-hs[i]) <= 0) {
      K2--;
    }
    us[K2++] = hs[i];
  }

  static double d1[100000], d2[100000];
  for (int i = 0; i < K1-1; i++) {
    const P d = ls[i+1] - ls[i];
    d1[i] = d.imag()/d.real();
  }
  for (int i = 0; i < K2-1; i++) {
    const P d = us[i+1] - us[i];
    d2[i] = d.imag()/d.real();
  }
  double x1, y1, x2, y2;
  while (scanf("%lf %lf %lf %lf", &x1, &y1, &x2, &y2) != EOF) {
    const double d = (y2-y1)/(x2-x1);
    const int i = lower_bound(d1, d1+K1-1, d) - d1;
    const int j = lower_bound(d2, d2+K2-1, d) - d2;
    const P p(x1, y1), q(x2, y2);
    if (cross(ls[i]-p, q-p) * cross(us[j]-p, q-p) < 0) {
      puts("BAD");
    } else {
      puts("GOOD");
    }
  }
  return 0;
}
