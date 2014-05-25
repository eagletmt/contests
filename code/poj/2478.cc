#include <iostream>
using namespace std;

int primes[100000];
int prime_size;

int phi(int n)
{
  int ans = n;
  for (int i = 0; primes[i]*primes[i] <= n; i++) {
    if (n % primes[i] == 0) {
      ans -= ans / primes[i];
      while (n % primes[i] == 0) {
        n /= primes[i];
      }
    }
  }
  if (n > 1) {
    ans -= ans / n;
  }
  return ans;
}

int main()
{
  static const int N = 1000000;
  static bool sieve[N+1];
  for (int i = 2; i <= N; i++) {
    if (!sieve[i]) {
      primes[prime_size++] = i;
      for (int j = i+i; j <= N; j += i) {
        sieve[j] = true;
      }
    }
  }
  static long long f[N+1];
  for (int i = 2; i <= N; i++) {
    f[i] = f[i-1] + phi(i);
  }

  int n;
  while (cin >> n && n != 0) {
    cout << f[n] << endl;
  }
  return 0;
}
