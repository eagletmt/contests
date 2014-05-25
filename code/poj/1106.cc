#include <cstdio>
#include <vector>
#include <complex>
#include <cmath>
#include <algorithm>
using namespace std;
typedef complex<double> P;
static const double PI = acos(-1.0);
static const double EPS = 1e-6;

int main()
{
  double x, y, r;
  while (scanf("%lf %lf %lf", &x, &y, &r) != EOF && r > 0.0) {
    const P center(x, y);
    int N;
    scanf("%d", &N);
    vector<P> v;
    for (int i = 0; i < N; i++) {
      scanf("%lf %lf", &x, &y);
      P p(x, y);
      p -= center;
      //if (abs(p) <= r) {
      if (abs(p) - r <= EPS) {
        v.push_back(p);
      }
    }
    N = v.size();

    int ans = 0;
    for (int i = 0; i < N; i++) {
      int c = 0;
      for (int j = 0; j < N; j++) {
        //if (fmod(2*PI + arg(v[(i+j)%N]) - arg(v[i]), 2*PI) <= PI) {
        if (fmod(2*PI + arg(v[(i+j)%N]) - arg(v[i]), 2*PI) - PI <= EPS) {
          ++c;
        }
      }
      ans = max(ans, c);
    }
    printf("%d\n", ans);
  }
  return 0;
}
