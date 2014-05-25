#include <cstdio>
#include <cmath>
using namespace std;
static const double PI = atan2(+0.0, -0.0);

struct point
{
  double x, y, z;
  double abs() const { return x*x + y*y + z*z; }
  double operator*(const point& that) const { return x*that.x + y*that.y + z*that.z; }
};

point read_point()
{
  int lat, lat_min, lon, lon_min;
  char ns, ew;
  scanf("%d %d %c %d %d %c", &lat, &lat_min, &ns, &lon, &lon_min, &ew);
  const double la = (ns == 'N' ? 1 : -1) * (lat + lat_min/60.0);
  const double lo = (ew == 'E' ? 1 : -1) * (lon + lon_min/60.0);
  const double theta = la / 180.0 * PI;
  const double phi = lo / 180.0 * PI;
  point p;
  p.x = cos(theta)*cos(phi);
  p.y = cos(theta)*sin(phi);
  p.z = sin(theta);
  return p;
}

double surface_distance(const point& p1, const point& p2)
{
  static const double R = 6370.0;
  return R * acos((p1 * p2) / (p1.abs() * p2.abs()));
}

int main()
{
  const point p1 = read_point();
  const point p2 = read_point();
  printf("%.3f\n", surface_distance(p1, p2));
  return 0;
}
