#include <cstdio>
#include <vector>
#include <cmath>
using namespace std;
static const double EPS = 1e-8;

int main()
{
  int N;
  scanf("%d", &N);
  vector<double> rs(N);
  for (int i = 0; i < N; i++) {
    scanf("%lf", &rs[i]);
  }

  vector<double> xs(rs);
  vector<bool> dispensable(N, false);
  double right = 2.0*rs[0];
  int ridx = 0;
  for (int i = 1; i < N; i++) {
    int k = -1;
    for (int j = 0; j < i; j++) {
      const double d = 2.0*sqrt(rs[i]*rs[j]) + xs[j];
      if (xs[i] - d < EPS) {
        xs[i] = d;
        k = j;
      }
    }
    for (int j = k+1; j < i; j++) {
      dispensable[j] = true;
    }

    if (right - (xs[i] + rs[i]) < EPS) {
      right = xs[i] + rs[i];
      ridx = i;
    }
  }

  for (int i = ridx+1; i < N; i++) {
    dispensable[i] = true;
  }

  int K = 0;
  for (int i = 0; i < N; i++) {
    if (dispensable[i]) {
      ++K;
    }
  }
  printf("%d\n", K);
  for (int i = 0; i < N; i++) {
    if (dispensable[i]) {
      printf("%d\n", i+1);
    }
  }
  return 0;
}
