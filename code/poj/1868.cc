#include <cstdio>
using namespace std;

bool check(const int *a, int N)
{
  for (int i = 0; i < N-2; i++) {
    for (int j = 1; i+2*j < N; j++) {
      if (a[i] < a[i+j] && a[i+j] < a[i+2*j]) {
        return false;
      }
      if (a[i] > a[i+j] && a[i+j] > a[i+2*j]) {
        return false;
      }
    }
  }
  return true;
}

int main()
{
  int N;
  while (scanf("%d", &N) != EOF && N != 0) {
    scanf("%*c");
    static int a[10000];
    for (int i = 0; i < N; i++) {
      int x;
      scanf("%d", &x);
      a[x] = i;
    }
    puts(check(a, N) ? "yes" : "no");
  }
  return 0;
}
