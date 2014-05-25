#include <stdio.h>

#define M 431

int main(void)
{
  static int primes[M];
  static int sieve[M+1];
  static int tbl[M+1][M+1];
  int *p = primes;
  int i, j;
  int N, K;

  for (i = 2; i <= M; i++) {
    if (!sieve[i]) {
      *p++ = i;
      for (j = i+i; j <= M; j += i) {
        sieve[j] = 1;
      }
    }
  }

  for (i = 0; i <= M; i++) {
    for (j = 0; primes[j] != 0; j++) {
      int s, t = primes[j];
      for (s = t; s <= i; s *= t) {
        tbl[i][t] += i / s;
      }
    }
  }

  while (scanf("%d %d", &N, &K) != EOF) {
    long long ans = 1LL;
    for (i = 0; primes[i] != 0; i++) {
      const int t = primes[i];
      ans *= 1LL + tbl[N][t] - tbl[K][t] - tbl[N-K][t];
    }
    printf("%lld\n", ans);
  }
  return 0;
}
