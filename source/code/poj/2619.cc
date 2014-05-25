#include <cstdio>
#include <algorithm>
using namespace std;

long long height(long long x)
{
  for (long long i = 1; ; i++) {
    if (x <= i*i) {
      return i;
    }
  }
}

int main()
{
  long long M, N;
  scanf("%lld %lld", &M, &N);
  if (M > N) {
    swap(M, N);
  }
  // M <= N
  long long h1 = height(M);
  long long x1 = M - (h1-1)*(h1-1);
  const long long h2 = height(N);
  const long long x2 = N - (h2-1)*(h2-1);
  int c = 0;
  while (h1 < h2) {
    if (h1 % 2 == M % 2) {
      // lower
      M += 2*h1;
      h1++;
      x1++;
      c++;
    } else {
      // upper
      if (x1 < x2) {
        // go down right
        M += 2*h1 + 1;
        x1 += 2;
      } else {
        // go down left
        M += 2*h1 - 1;
      }
      ++h1;
      c += 2;
    }
  }
  if (N < M) {
    swap(N, M);
  }
  printf("%lld\n", c + N - M);
  return 0;
}
