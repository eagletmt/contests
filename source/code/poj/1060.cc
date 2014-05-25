#include <cstdio>
#include <bitset>
using namespace std;
static const int N = 2000;

pair<int, bitset<N+N> > read()
{
  int n;
  scanf("%d", &n);
  bitset<N+N> f;
  for (int i = 0; i < n; i++) {
    int x;
    scanf("%d", &x);
    f.set(n-i-1, x);
  }
  return make_pair(n, f);
}

int main()
{
  int T;
  scanf("%d", &T);
  while (T-- > 0) {
    pair<int, bitset<N+N> > f, g, h;
    f = read();
    g = read();
    h = read();
    bitset<N+N> fg;
    for (int i = 0; i < N; i++) {
      if (f.second.test(i)) {
        fg ^= g.second;
      }
      g.second <<= 1;
    }
    const int M = h.first-1;
    h.second <<= (N-M);
    bitset<N+N> a;
    for (int i = N-M; i >= 0; i--) {
      if (fg.test(i+M)) {
        a.set(i);
        fg ^= h.second;
      }
      h.second >>= 1;
    }
    int i;
    for (i = N-1; !fg.test(i); i--);
    printf("%d", i+1);
    for (; i >= 0; i--) {
      printf(" %d", fg.test(i));
    }
    putchar('\n');
  }
  return 0;
}
