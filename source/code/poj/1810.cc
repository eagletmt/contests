#include <cstdio>
#include <algorithm>
using namespace std;

int main()
{
  int T;
  scanf("%d", &T);
  while (T-- > 0) {
    int K, N, M;
    scanf("%d %d %d\n", &K, &N, &M);
    static int a[1000][1000];
    for (int i = 0; i < N; i++) {
      fill_n(a[i], N, 0);
    }
    for (int i = 0; i < K; i++) {
      double x, y;
      scanf("%lf %lf", &x, &y);
      ++a[int(y)][int(x)];
    }

    static int sums[1001][1001];
    for (int i = 0; i <= N; i++) {
      fill_n(sums[i], N+1, 0);
    }
    for (int i = 0; i < N; i++) {
      for (int j = 0; j < N; j++) {
        sums[i+1][j+1] = sums[i][j+1] + sums[i+1][j] - sums[i][j] + a[i][j];
      }
    }
    int ansx = -1, ansy = -1, ans = 0;
    for (int i = 0; i+M <= N; i++) {
      for (int j = 0; j+M <= N; j++) {
        const int n = sums[i+M][j+M] - sums[i][j+M] - sums[i+M][j] + sums[i][j];
        if (n > ans) {
          ans = n;
          ansx = j;
          ansy = i;
        } else if (n == ans) {
          if (ansy < i) {
            ansx = j;
            ansy = i;
          } else if (ansy == i && ansx < j) {
            ansx = j;
          }
        }
      }
    }
    printf("%d %d\n", ansx, ansy);
  }
  return 0;
}
