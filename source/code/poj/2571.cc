#include <cstdio>
#include <cmath>
using namespace std;
static const double PI = acos(-1.0);
static const double EPS = 1e-6;

struct P3
{
  double x, y, z;
  P3() {}
  P3(double a, double b, double c) : x(a), y(b), z(c) {}
};
inline double dot(const P3& p, const P3& q) { return p.x*q.x + p.y*q.y + p.z*q.z; }
inline double abs(const P3& p) { return sqrt(dot(p, p)); }

static const double R = 6378;

P3 from_polar(double lat, double lan, double r)
{
  lat = lat/180.0*PI;
  lan = lan/180.0*PI;
  double x = r*cos(lat)*cos(lan);
  double y = r*cos(lat)*sin(lan);
  double z = r*sin(lat);
  return P3(x, y, z);
}

int main()
{
  int N;
  for (int Ti = 1; scanf("%d", &N) != EOF && N != 0; Ti++) {
    double lat, lan, height;
    scanf("%lf %lf %lf", &lat, &lan, &height);
    const P3 sat = from_polar(lat, lan, R + height);
    const double u = R / (R + height);
    printf("Test case %d:\n", Ti);
    for (int i = 0; i < N; i++) {
      char name[128];
      scanf("%s %lf %lf", name, &lat, &lan);
      const P3 p = from_polar(lat, lan, R);
      const double t = dot(sat, p)/(abs(sat) * abs(p));
      if (u - t < EPS) {
        puts(name);
      }
    }
    putchar('\n');
  }
  return 0;
}
