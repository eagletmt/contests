#include <cstdio>
#include <algorithm>
using namespace std;

int main()
{
  static char s[1000001];
  scanf("%s", s);
  int ans = 0;
  for (const char *p = s; *p != 0;) {
    static const char joi[] = "JOI";
    int cs[3];
    for (int i = 0; i < 3; i++) {
      cs[i] = 0;
      while (*p != 0 && *p == joi[i]) {
        ++cs[i];
        ++p;
      }
    }
    if (cs[0] >= cs[1] && cs[2] >= cs[1]) {
      ans = max(ans, cs[1]);
    }
  }
  printf("%d\n", ans);
  return 0;
}
