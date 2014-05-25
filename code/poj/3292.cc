#include <cstdio>
#include <vector>
using namespace std;

int main()
{
  static const int M = 1000001;
  static bool sieve[M+1];
  vector<int> primes;
  for (int i = 5; i <= M; i += 4) {
    if (!sieve[i]) {
      primes.push_back(i);
      for (int j = 5; i*j <= M; j += 4) {
        sieve[i*j] = true;
      }
    }
  }
  static int cnt[M+1];
  for (vector<int>::const_iterator it = primes.begin(); it != primes.end(); ++it) {
    for (vector<int>::const_iterator jt = it; jt != primes.end() && *jt <= M / *it; ++jt) {
      cnt[*it * *jt] = 1;
    }
  }
  for (int i = 1; i <= M; i++) {
    cnt[i] += cnt[i-1];
  }

  int H;
  while (scanf("%d", &H) != EOF && H != 0) {
    printf("%d %d\n", H, cnt[H]);
  }
  return 0;
}
