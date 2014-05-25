#include <cstdio>
#include <algorithm>
using namespace std;

int main()
{
  int T;
  scanf("%d", &T);
  while (T-- > 0) {
    int R, C;
    scanf("%d %d", &R, &C);
    static long long sums[1001][1001];
    for (int i = 0; i <= R; i++) {
      fill_n(sums[i], C+1, 0);
    }
    for (int i = 0; i < R; i++) {
      for (int j = 0; j < C; j++) {
        int x;
        scanf("%d", &x);
        sums[i+1][j+1] = sums[i][j+1] + sums[i+1][j] - sums[i][j] + x;
      }
    }

    int D;
    scanf("%d", &D);
    while (D-- > 0) {
      int r1, c1, r2, c2;
      scanf("%d %d %d %d", &r1, &c1, &r2, &c2);
      printf("Absolutni hodnota pohodlnosti je %lld bodu.\n", sums[r2][c2] - sums[r1-1][c2] - sums[r2][c1-1] + sums[r1-1][c1-1]);
    }
    putchar('\n');
  }
  return 0;
}
