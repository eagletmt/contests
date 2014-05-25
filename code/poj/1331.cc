#include <cstdio>
#include <algorithm>
using namespace std;

int conv(int x, int base)
{
  int r = 0;
  int e = 1;
  while (x > 0) {
    r += (x%10) * e;
    x /= 10;
    e *= base;
  }
  return r;
}

int main()
{
  int T;
  scanf("%d", &T);
  while (T-- > 0) {
    int p, q, r;
    scanf("%d %d %d", &p, &q, &r);
    int base = 0;
    for (int x = p; x > 0; x /= 10) {
      base = max(base, x%10);
    }
    for (int x = q; x > 0; x /= 10) {
      base = max(base, x%10);
    }
    for (int x = r; x > 0; x /= 10) {
      base = max(base, x%10);
    }
    for (++base; base <= 16; ++base) {
      if (conv(p, base) * conv(q, base) == conv(r, base)) {
        printf("%d\n", base);
        goto NEXT;
      }
    }
    puts("0");
NEXT:
    ;
  }
  return 0;
}
