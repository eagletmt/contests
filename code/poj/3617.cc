#include <cstdio>
using namespace std;

int main()
{
  int N;
  scanf("%d", &N);
  static char s[30001];
  for (int i = 0; i < N; i++) {
    scanf("%1s", &s[i]);
  }

  static char buf[30001];
  char *p = buf;
  for (int beg = 0, end = N-1; beg <= end;) {
    int b = beg, e = end;
    while (b <= e && s[b] == s[e]) {
      b++;
      e--;
    }
    if (s[b] <= s[e]) {
      *p++ = s[beg++];
    } else {
      *p++ = s[end--];
    }
  }
  for (int i = 0; i < N; i += 80) {
    for (int j = 0; j < 80 && i+j < N; j++) {
      putchar(buf[i+j]);
    }
    putchar('\n');
  }
  return 0;
}
