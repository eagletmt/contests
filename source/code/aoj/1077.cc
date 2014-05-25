#include <cstdio>
#include <algorithm>
using namespace std;

int main()
{
  int a, b, c, d, e, f;
  while (scanf("%d %d %d %d %d %d", &a, &b, &c, &d, &e, &f) != EOF && a+b+c+d+e+f != 0) {
    int x = a + d;
    int y = b + e;
    int z = c + f;
    int w = min(x, min(y, z));
    int ans = 0;
    for (int i = max(0, w-2); i <= w; i++) {
      ans = max(ans, i + (x-i)/3 + (y-i)/3 + (z-i)/3);
    }
    printf("%d\n", ans);
  }
  return 0;
}
