#include <stdio.h>
#include <ctype.h>

int check(const char *p, char args[1000][50010])
{
  int c = 0;
  while (*p != '\0' && *p != '\n') {
    if (*p == '%') {
      ++p;
      if (*p == 'd') {
        if (args[c][0] == '\0' || args[c][0] == '\n') {
          return -1;
        }
        int i;
        for (i = 0; args[c][i] != '\0' && args[c][i] != '\n'; i++) {
          if (!isdigit(args[c][i])) {
            return -1;
          }
        }
        ++c;
      } else if (*p == 's') {
        ++c;
      } else if (*p == '%') {
      } else {
        return -1;
      }
    }
    ++p;
  }
  return c;
}

void format(const char *p, char args[1000][50010])
{
  int c = 0;
  while (*p != '\0' && *p != '\n') {
    if (*p == '%') {
      ++p;
      if (*p == 'd') {
        int i;
        for (i = 0; args[c][i] != '\0' && args[c][i] != '\n' && args[c][i] == '0'; i++);
        if (args[c][i] == '\0' || args[c][i] == '\n') {
          putchar('0');
        } else {
          for (; args[c][i] != '\0' && args[c][i] != '\n'; i++) {
            putchar(args[c][i]);
          }
        }
        ++c;
      } else if (*p == 's') {
        int i;
        for (i = 0; args[c][i] != '\0' && args[c][i] != '\n'; i++) {
          putchar(args[c][i]);
        }
        ++c;
      } else {
        putchar('%');
      }
    } else {
      putchar(*p);
    }
    ++p;
  }
  putchar('\n');
}

int main(void)
{
  static char fmt[50010];
  fgets(fmt, sizeof fmt, stdin);
  static char args[1000][50010];
  int N = 0;
  while (fgets(args[N], sizeof args[N], stdin) != NULL) {
    N++;
  }
  if (check(fmt, args) != N) {
    puts("ERROR");
  } else {
    format(fmt, args);
  }
  return 0;
}
