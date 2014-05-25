#include <cstdio>
#include <utility>
using namespace std;

int main()
{
  int T;
  scanf("%d", &T);
  while (T-- > 0) {
    static char buf[10001];
    scanf("%s", buf);
    static pair<int,int> nodes[10000];
    static int mem[10000];
    int sp = 0;
    int i;
    for (i = 0; buf[i] != '\0'; ++i) {
      pair<int,int>& e = nodes[i];
      if ('a' <= buf[i] && buf[i] <= 'z') {
        e.first = e.second = -1;
        mem[sp++] = i;
      } else {
        e.first = mem[--sp];
        e.second = mem[sp-1];
        mem[sp-1] = i;
      }
    }

    static char out[10001];
    out[i] = '\0';
    int head = 0, tail = 1;
    while (head < tail) {
      const int idx = mem[head++];
      const pair<int,int>& e = nodes[idx];
      out[--i] = buf[idx];
      if (e.first != -1) {
        mem[tail++] = e.second;
        mem[tail++] = e.first;
      }
    }
    puts(out);
  }
  return 0;
}
