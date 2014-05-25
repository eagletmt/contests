#include <cstdio>
#include <algorithm>
using namespace std;

static const int K = 6174;

pair<int,int> f(int N)
{
  int a[4];
  int d = 0;
  for (; d < 4 && N != 0; d++) {
    a[d] = N%10;
    N /= 10;
  }
  sort(a, a+d);
  int x = 0, y = 0;
  for (int i = 0; i < d; i++) {
    x = 10*x + a[d-i-1];
    y = 10*y + a[i];
  }
  return make_pair(x, y);
}

int main()
{
  int N;
  while (scanf("%d", &N) != EOF && N != -1) {
    printf("N=%d:\n", N);
    if (N/1000 > 0 && N/10000 == 0) {
      pair<int,int> r = f(N);
      if (r.first == r.second) {
        puts("No!!");
      } else {
        int c = 0;
        while (N != 0 && N != K) {
          r = f(N);
          printf("%d-%d=%d\n", r.first, r.second, r.first-r.second);
          N = r.first - r.second;
          c++;
        }
        printf("Ok!! %d times\n", c);
      }
    } else {
      puts("No!!");
    }
  }
  return 0;
}
