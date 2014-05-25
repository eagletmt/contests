#include <cstdio>
#include <vector>
#include <cmath>
using namespace std;

long long det(const long long a[3][3])
{
  long long r = 0LL;
  for (int i = 0; i < 3; i++) {
    const int j = (i+1) % 3;
    const int k = (j+1) % 3;
    r += a[0][i]*(a[1][j]*a[2][k] - a[1][k]*a[2][j]);
  }
  return r;
}

int main()
{
  int T;
  scanf("%d", &T);
  while (T-- > 0) {
    long long a[3][3];
    long long b[3];
    for (int i = 0; i < 3; i++) {
      for (int j = 0; j < 3; j++) {
        scanf("%lld", &a[i][j]);
      }
      scanf("%lld", &b[i]);
    }

    long long d[3];
    for (int i = 0; i < 3; i++) {
      for (int j = 0; j < 3; j++) {
        swap(a[j][i], b[j]);
      }
      d[i] = det(a);
      printf("%lld ", d[i]);
      for (int j = 0; j < 3; j++) {
        swap(a[j][i], b[j]);
      }
    }
    const long long e = det(a);
    printf("%lld\n", e);
    if (e == 0LL) {
      puts("No unique solution");
    } else {
      printf("Unique solution:");
      for (int i = 0; i < 3; i++) {
        double f = double(d[i]) / e;
        if (fabs(f) < 1e-4) {
          f = 0.000;
        }
        printf(" %.3f", f);
      }
      putchar('\n');
    }
    putchar('\n');
  }
  return 0;
}
