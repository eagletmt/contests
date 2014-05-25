#include <cstdio>
#include <limits>
#include <algorithm>
using namespace std;

long long solve(int u, int d, int N)
{
  const long long m = (static_cast<long long>(N)*u-1LL)/(u+d);
  const long long n = N - m;
  return u*n - m*d;
}

int main()
{
  int N, M;
  scanf("%d %d", &N, &M);
  long long ans = numeric_limits<long long>::max();
  for (int i = 0; i < M; i++) {
    int u, d;
    scanf("%d %d", &u, &d);
    ans = min(ans, solve(u, d, N));
  }
  printf("%lld\n", ans);
  return 0;
}
