#include <cstdio>
#include <vector>
using namespace std;

int main()
{
  int N;
  while (scanf("%d", &N) != EOF && N != 0) {
    vector<long long> ks(N);
    long long x = 0LL;
    for (int i = 0; i < N; i++) {
      scanf("%lld", &ks[i]);
      x ^= ks[i];
    }

    int c = 0;
    for (int i = 0; i < N; i++) {
      if ((x ^ ks[i]) < ks[i]) {
        ++c;
      }
    }
    printf("%d\n", c);
  }
  return 0;
}
