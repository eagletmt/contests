#include <cstdio>
using namespace std;

int main()
{
  int N;
  while (scanf("%d", &N) != EOF && N != 0) {
    long long ans = 0LL, acc = 0LL;
    scanf("%lld", &acc);
    for (int i = 1; i < N; i++) {
      int a;
      scanf("%d", &a);
      ans += acc < 0 ? -acc : acc;
      acc += a;
    }
    printf("%lld\n", ans);
  }
  return 0;
}
