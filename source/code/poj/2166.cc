#include <cstdio>
#include <algorithm>
using namespace std;

int main()
{
  int N;
  scanf("%d", &N);
  static int a[50001];
  for (int n = 1; n < N; n++) {
    a[1] = n;
    a[n] = 1;
    for (int i = n; i != 1; i /= 2) {
      swap(a[i/2], a[i]);
    }
  }
  a[N] = 1;
  printf("%d", N);
  for (int i = 2; i <= N; i++) {
    printf(" %d", a[i]);
  }
  putchar('\n');
  return 0;
}
