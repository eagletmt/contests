#include <iostream>
#include <cstdio>
#include <complex>
using namespace std;
typedef complex<double> P;
static const double EPS = 1e-4;
static const P P_EPS = P(EPS, EPS);

int main()
{
  P a, b, c, d;
  while (cin >> a.real() >> a.imag() >> b.real() >> b.imag()
      >> c.real() >> c.imag() >> d.real() >> d.imag()) {

    if (abs(a-b) < EPS) {
      // a = c, b = d, c = a&b
      b = c;
      c = a;
      b = d;
      a = b;
    } else if (abs(b-c) < EPS) {
      // a=a, b=d, c=b&c
      b = d;
    } else if (abs(c-d) < EPS) {
      // a=a, b=b, c=c&d
    } else if (abs(a-c) < EPS) {
      // a=d, b=b, c=a&c
      a = d;
    } else if (abs(b-d) < EPS) {
      // a=a, b=c, c=b&d
      b = c;
      c = d;
    } else {
      // a=c, b=b, c=a&d
      a = c;
      c = d;
    }

    P ans = a + b -c;
    printf("%.3f %.3f\n", ans.real(), ans.imag());
  }
  return 0;
}
