#include <cstdio>
using namespace std;

int f(int n)
{
  int x = n;
  while (n > 0) {
    x += n % 10;
    n /= 10;
  }
  return x;
}

int main()
{
  static const int M = 10000;
  static bool a[M];
  for (int i = 1; i <= M; i++) {
    const int d = f(i);
    if (d <= M) {
      a[d-1] = true;
    }
  }
  for (int i = 0; i < M; i++) {
    if (!a[i]) {
      printf("%d\n", i+1);
    }
  }
  return 0;
}
