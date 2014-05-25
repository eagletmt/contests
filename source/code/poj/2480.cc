#include <cstdio>
#include <vector>
using namespace std;

long long phi(long long n)
{
  long long ans = n;
  for (long long i = 2LL; i*i <= n; i++) {
    if (n % i == 0LL) {
      ans -= ans / i;
      while (n % i == 0LL) {
        n /= i;
      }
    }
  }
  if (n > 1) {
    ans -= ans / n;
  }
  return ans;
}

vector<long long> factorize(long long n)
{
  vector<long long> fs;
  for (long long i = 1LL; i*i <= n; i++) {
    if (n % i == 0LL) {
      fs.push_back(i);
      if (i*i != n) {
        fs.push_back(n/i);
      }
    }
  }
  return fs;
}
int main()
{
  long long N;
  while (scanf("%lld", &N) != EOF) {
    long long ans = 0;
    const vector<long long> fs = factorize(N);
    ans = 0;
    for (vector<long long>::const_iterator it = fs.begin(); it != fs.end(); ++it) {
      ans += *it * phi(N / *it);
    }
    printf("%lld\n", ans);
  }
  return 0;
}
