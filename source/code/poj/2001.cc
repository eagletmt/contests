#include <cstdio>
#include <cstring>
#include <map>
using namespace std;

struct fixed_string
{
  char s[25];
  fixed_string(const char *t) { strcpy(s, t); }
  fixed_string(const fixed_string& t) { strcpy(s, t.s); }
  bool operator<(const fixed_string& t) const { return strcmp(s, t.s) < 0; }
};

int main()
{
  map<fixed_string, int> m;
  static char a[1000][25];
  int N = 0;
  while (scanf("%s", a[N]) != EOF) {
    for (int i = 1; a[N][i-1] != '\0'; i++) {
      char c = a[N][i];
      a[N][i] = '\0';
      fixed_string fs(a[N]);
      ++m[fs];
      a[N][i] = c;
    }
    N++;
  }

  for (int i = 0; i < N; i++) {
    fixed_string fs(a[i]);
    int j = 1;
    for (; a[i][j] != '\0'; j++) {
      char c = fs.s[j];
      fs.s[j] = '\0';
      if (m[fs] > 1) {
        fs.s[j] = c;
      } else {
        break;
      }
    }
    printf("%s %s\n", a[i], fs.s);
  }
  return 0;
}
