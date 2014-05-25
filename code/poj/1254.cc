#include <cstdio>
#include <complex>
#include <cmath>
using namespace std;
typedef complex<double> P;
static const double PI = acos(-1.0);

inline double cross(const P& a, const P& b)
{
  return a.real()*b.imag() - b.real()*a.imag();
}

struct line
{
  P base, dir;
  inline P intersection(const line& ln) const
  {
    return base + dir*(cross(ln.dir, ln.base - base))/cross(ln.dir, dir);
  }
};

int main()
{
  int T;
  scanf("%d", &T);
  while (T-- > 0) {
    line ls[2];
    for (int i = 0; i < 2; i++) {
      int x, y, theta;
      scanf("%d %d %d", &x, &y, &theta);
      ls[i].base = P(x, y);
      ls[i].dir = polar(1.0, (270-theta)/180.0*PI);
    }
    const P p = ls[0].intersection(ls[1]);
    printf("%.4f %.4f\n", p.real(), p.imag());
  }
  return 0;
}
