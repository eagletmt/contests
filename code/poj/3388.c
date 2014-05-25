#include <stdio.h>

int f(int x, int K, const int *a)
{
  int i, n = 0;
  for (i = 0; i < K; i++) {
    n += a[i]/x;
  }
  return n;
}

int main()
{
  int N, K;
  int i, j;
  static int a[50000];
  int lo, hi;
  int c;

  scanf("%d %d", &N, &K);
  for (i = 0; i < K; i++) {
    scanf("%d", &a[i]);
  }

  lo = 1; hi = N;
  while (lo+1 < hi) {
    const int mid = (lo + hi)/2;
    const int x = f(mid, K, a);
    if (x >= N) {
      lo = mid;
    } else {
      hi = mid;
    }
  }
  if (f(hi, K, a) >= N) {
    lo = hi;
  }
  printf("%d\n", lo);
  c = 0;
  for (i = 0; i < K && c < N; i++) {
    for (j = 0; j < a[i]/lo && c < N; j++, c++) {
      printf("%d\n", i+1);
    }
  }
  return 0;
}
