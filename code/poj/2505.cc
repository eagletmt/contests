#include <cstdio>
using namespace std;

int main()
{
  long long n;
  while (scanf("%lld", &n) != EOF) {
    long long p = 1;
    for (;;) {
      p *= 9;
      if (p >= n) {
        puts("Stan wins.");
        break;
      }
      p *= 2;
      if (p >= n) {
        puts("Ollie wins.");
        break;
      }
    }
  }
  return 0;
}
