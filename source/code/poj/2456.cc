#include <cstdio>
#include <algorithm>
using namespace std;

bool ok(const long long *a, int N, int C, long long d)
{
  const long long *p = a;
  for (int i = 1; i < C; i++) {
    const long long x = *p;
    p = lower_bound(p, a+N, x+d);
    if (p == a+N) {
      return false;
    }
  }
  return true;
}

int main()
{
  int N, C;
  scanf("%d %d", &N, &C);
  static long long a[100000];
  for (int i = 0; i < N; i++) {
    scanf("%lld", &a[i]);
  }
  sort(a, a+N);

  long long left = 1LL, right = 1000000000LL;
  while (left < right) {
    const long long mid = (left + right + 1LL) / 2LL;
    if (ok(a, N, C, mid)) {
      left = mid;
    } else {
      right = mid-1LL;
    }
  }
  printf("%lld\n", left);
  return 0;
}
