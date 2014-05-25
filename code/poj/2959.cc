#include <cstdio>
#include <cmath>
using namespace std;
static const double PI = acos(-1.0);

int main()
{
  int T;
  scanf("%d", &T);
  while (T-- > 0) {
    double D, d, s;
    scanf("%lf %lf %lf", &D, &d, &s);
    printf("%d\n", int(PI/asin((s+d)/(D-d))));
  }
  return 0;
}
