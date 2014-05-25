#include <cstdio>
#include <cmath>
#include <complex>
using namespace std;
typedef complex<double> P;
static const double PI = acos(-1.0);

double solve(double r, double h, double d1, double d2, double theta)
{
  const double phi = theta * r / sqrt(r*r + h*h);
  return sqrt(d1*d1 + d2*d2 - 2*d1*d2*cos(phi));
}

int main()
{
  double r, h, d1, A1, d2, A2;
  while (scanf("%lf %lf %lf %lf %lf %lf", &r, &h, &d1, &A1, &d2, &A2) != EOF) {
    const double t1 = A1 * PI/180.0;
    const double t2 = A2 * PI/180.0;
    const double theta = fabs(t2 - t1);
    printf("%.2f\n", min(solve(r, h, d1, d2, theta), solve(r, h, d1, d2, 2*PI - theta)));
  }
  return 0;
}
