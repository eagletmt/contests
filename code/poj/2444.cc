#include <cstdio>
#include <algorithm>
using namespace std;

inline long long ABS(long long x) { return x >= 0 ? x : -x; }

int main()
{
  int M, N;
  while (scanf("%d %d", &M, &N) != EOF && M != 0) {
    static long long a[501][501];
    for (int i = 0; i <= 500; i++) {
      a[i][0] = a[0][i] = 0;
    }
    for (int i = 1; i <= M; i++) {
      for (int j = 1; j <= N; j++) {
        int x;
        scanf("%d", &x);
        a[i][j] = a[i-1][j] + a[i][j-1] - a[i-1][j-1] + x;
      }
    }

    long long ans = 1LL<<60;
    for (int i = 1; i < M; i++) {
      for (int j = 1; j < N; j++) {
        {
          // XY
          // ZZ
          long long X = a[i][j];
          long long Y = a[i][N] - a[i][j];
          long long Z = a[M][N] - (X + Y);
          ans = min(ans, ABS(X - Y) + ABS(Y - Z) + ABS(Z - X));
        }
        {
          // XX
          // YZ
          long long X = a[i][N];
          long long Y = a[M][j] - a[i][j];
          long long Z = a[M][N] - (X + Y);
          ans = min(ans, ABS(X - Y) + ABS(Y - Z) + ABS(Z - X));
        }
        {
          // XY
          // XZ
          long long X = a[M][j];
          long long Y = a[i][N] - a[i][j];
          long long Z = a[M][N] - (X + Y);
          ans = min(ans, ABS(X - Y) + ABS(Y - Z) + ABS(Z - X));
        }
        {
          // XZ
          // YZ
          long long X = a[i][j];
          long long Y = a[M][j] - a[i][j];
          long long Z = a[M][N] - (X + Y);
          ans = min(ans, ABS(X - Y) + ABS(Y - Z) + ABS(Z - X));
        }
      }
    }
    for (int i = 1; i < M; i++) {
      for (int j = i+1; j < M; j++) {
        // X
        // Y
        // Z
        long long X = a[i][N];
        long long Y = a[j][N] - X;
        long long Z = a[M][N] - (X + Y);
        ans = min(ans, ABS(X - Y) + ABS(Y - Z) + ABS(Z - X));
      }
    }
    for (int i = 1; i < N; i++) {
      for (int j = i+1; j < N; j++) {
        // X Y Z
        long long X = a[M][i];
        long long Y = a[M][j] - X;
        long long Z = a[M][N] - (X + Y);
        ans = min(ans, ABS(X - Y) + ABS(Y - Z) + ABS(Z - X));
      }
    }
    printf("%lld\n", ans);
  }
  return 0;
}
