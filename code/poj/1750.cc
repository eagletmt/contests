#include <cstdio>
#include <cstring>
using namespace std;

int next_offset(int off, const char *prev, const char *cur)
{
  int i, j, k;
  for (i = j = k = 0;
      i < off+1 && prev[j] != '\0' && cur[k] != '\0' && prev[j] == cur[k];
      ++i, ++j, ++k);
  return i;
}

void indent(int n)
{
  for (int i = 0; i < n; i++) {
    putchar(' ');
  }
}

int main()
{
  char prev[16], cur[16];
  scanf("%s", prev);
  puts(prev);
  for (int off = 0; scanf("%s", cur) != EOF; memcpy(prev, cur, 11)) {
    off = next_offset(off, prev, cur);
    indent(off);
    puts(cur);
  }
  return 0;
}
