#include <cstdio>
using namespace std;

bool solve(int N, int M, int ans[15][15], const int b[15][15])
{
  int m = 1000;
  int a[15][15];
  for (unsigned s = 0; s < (1<<N); s++) {
    for (int j = 0; j < N; j++) {
      a[0][N-j-1] = (s & (1<<j)) != 0;
    }
    static const int di[] = {0, 0, 0, -1};
    static const int dj[] = {0, -1, 1, 0};
    int flip = 0;
    for (int i = 0; i < M-1; i++) {
      for (int j = 0; j < N; j++) {
        int c = b[i][j];
        for (int d = 0; d < 4; d++) {
          const int k = i + di[d];
          const int l = j + dj[d];
          if (0 <= k && k < M && 0 <= l && l < N) {
            c ^= a[k][l];
          }
        }
        a[i+1][j] = c;
      }
    }
    for (int j = 0; j < N; j++) {
      int c = b[M-1][j];
      for (int d = 0; d < 4; d++) {
        const int k = M-1 + di[d];
        const int l = j + dj[d];
        if (0 <= k && k < M && 0 <= l && l < N) {
          c ^= a[k][l];
        }
      }
      if (c != 0) {
        goto FAIL;
      }
    }

    for (int i = 0; i < M; i++) {
      for (int j = 0; j < N; j++) {
        flip += a[i][j];
      }
    }
    if (flip < m) {
      m = flip;
      for (int i = 0; i < M; i++) {
        for (int j = 0; j < N; j++) {
          ans[i][j] = a[i][j];
        }
      }
    }
FAIL:
    ;
  }
  return m < 1000;
}

int main()
{
  int M, N;
  scanf("%d %d", &M, &N);
  int b[15][15];
  for (int i = 0; i < M; i++) {
    for (int j = 0; j < N; j++) {
      scanf("%d", &b[i][j]);
    }
  }
  int ans[15][15];
  if (solve(N, M, ans, b)) {
    for (int i = 0; i < M; i++) {
      for (int j = 0; j < N; j++) {
        if (j != 0) {
          putchar(' ');
        }
        printf("%d", ans[i][j]);
      }
      putchar('\n');
    }
  } else {
    puts("IMPOSSIBLE");
  }
  return 0;
}
