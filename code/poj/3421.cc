#include <cstdio>
#include <vector>
using namespace std;

int main()
{
  long long fact[21];
  fact[0] = 1LL;
  for (int i = 1; i <= 20; i++) {
    fact[i] = i*fact[i-1];
  }

  vector<int> primes;
  static const int M = (1<<11);
  static bool sieve[M+1];
  for (int i = 2; i <= M; i++) {
    if (!sieve[i]) {
      primes.push_back(i);
      for (int j = i+i; j <= M; j += i) {
        sieve[j] = true;
      }
    }
  }

  int x;
  while (scanf("%d", &x) != EOF) {
    int a = 0;
    long long b = 1LL;
    for (vector<int>::const_iterator it = primes.begin(); it != primes.end() && *it <= x; ++it) {
      int c = 0;
      while (x % *it == 0) {
        x /= *it;
        ++c;
      }
      a += c;
      b *= fact[c];
    }
    if (x != 1) {
      ++a;
    }
    printf("%d %lld\n", a, fact[a]/b);
  }
  return 0;
}
