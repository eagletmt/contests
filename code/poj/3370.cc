#include <cstdio>
#include <algorithm>
using namespace std;

int main()
{
  int C, N;
  while (scanf("%d %d", &C, &N) != EOF && C != 0) {
    static const int K = 100000;
    static int prev[K];
    fill_n(prev, N, -1);
    int b = -1, e = -1;
    int acc = 0;
    for (int i = 0; i < N; i++) {
      int x;
      scanf("%d", &x);
      acc = (acc + x) % C;
      if (x % C == 0) {
        b = e = i;
      } else if (acc == 0) {
        if (b == -1 || i < e-b) {
          b = 0;
          e = i;
        }
      } else if (prev[acc] != -1) {
        if (b == -1 || i-prev[acc]-1 < e-b) {
          b = prev[acc]+1;
          e = i;
        }
      } else {
        prev[acc] = i;
      }
    }
    printf("%d", b+1);
    for (int i = b+1; i <= e; i++) {
      printf(" %d", i+1);
    }
    putchar('\n');
  }
  return 0;
}
