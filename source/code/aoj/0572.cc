#include <cstdio>
#include <algorithm>
using namespace std;

int f(const int *it, const int *ilast, const int *jt, const int *jlast)
{
  int c = 0;
  for (; it != ilast && jt != jlast; ++it) {
    if (*it == *jt) {
      ++c;
      ++jt;
    }
  }
  return c;
}

int main()
{
  int A, B;
  scanf("%d %d", &A, &B);
  static int as[5000], bs[5000];
  for (int i = 0; i < A; i++) {
    scanf("%d", &as[i]);
  }
  for (int j = 0; j < B; j++) {
    scanf("%d", &bs[j]);
  }

  int ans = 0;
  for (int j = 0; j < B; j++) {
    ans = max(ans, f(as, as+A, bs+j, bs+B));
  }
  printf("%d\n", ans);
  return 0;
}
