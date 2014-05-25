#include <cstdio>
#include <algorithm>
using namespace std;

struct line
{
  int id, a, b, c;
  bool operator<(const line& l) const
  {
    if (a == l.a) {
      return b < l.b;
    } else {
      return a < l.a;
    }
  }
};

void check(bool *invalid, const line *xs, int N)
{
  for (int i = 0; i < N-1;) {
    const int a = xs[i].a;
    const int id = xs[i].id;
    int end = xs[i].c;
    for (i++; i < N && xs[i].a == a && xs[i].b <= end; i++) {
      invalid[id] = invalid[xs[i].id] = true;
      end = max(end, xs[i].c);
    }
  }
}

int main()
{
  int N;
  scanf("%d", &N);
  static line xs[50000], ys[50000];
  for (int i = 0; i < N; i++) {
    int a, b, c, d;
    scanf("%d %d %d %d", &a, &b, &c, &d);
    line &x1 = xs[2*i], &x2 = xs[2*i+1];
    x1.id = x2.id = i;
    x1.b = x2.b = b;
    x1.c = x2.c = d;
    x1.a = a;
    x2.a = c;

    line &y1 = ys[2*i], &y2 = ys[2*i+1];
    y1.id = y2.id = i;
    y1.b = y2.b = a;
    y1.c = y2.c = c;
    y1.a = b;
    y2.a = d;
  }
  sort(xs, xs+2*N);
  sort(ys, ys+2*N);

  static bool invalid[25000];
  check(invalid, xs, 2*N);
  check(invalid, ys, 2*N);
  int ans = 0;
  for (int i = 0; i < N; i++) {
    if (!invalid[i]) {
      ++ans;
    }
  }
  printf("%d\n", ans);
  return 0;
}
