#include <iostream>
#include <algorithm>
#include <complex>
#include <cmath>
using namespace std;
typedef complex<double> P;
static const double PI = acos(-1.0);

inline double dot(const P& a, const P& b)
{
  return a.real()*b.real() + a.imag()*b.imag();
}

bool solve(int r, const P& p1, const P& p2, const P& p3)
{
  const double r1 = abs(p1);
  const double r2 = abs(p2);
  const double r3 = abs(p3);
  if (r1 > r || r2 > r || r3 > r) {
    return false;
  }
  const double ang[3] = {
    acos(dot(p1, p2) / (r1 * r2)),
    acos(dot(p2, p3) / (r2 * r3)),
    acos(dot(p3, p1) / (r3 * r1)),
  };
  return *max_element(ang, ang+3) > 2*PI/3.0;
}

int main()
{
  int T;
  cin >> T;
  while (T-- > 0) {
    int r, x1, y1, x2, y2, x3, y3;
    cin >> r >> x1 >> y1 >> x2 >> y2 >> x3 >> y3;
    if ((x1 == 0 && y1 == 0) || (x2 == 0 && y2 == 0) || (x3 == 0 && y3 == 0)) {
      cout << "No" << endl;
    } else {
      cout << (solve(r, P(x1,y1), P(x2,y2), P(x3,y3)) ? "Yes" : "No") << endl;
    }
  }
  return 0;
}
