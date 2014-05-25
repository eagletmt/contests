#include <cstdio>
#include <algorithm>
using namespace std;

struct rect
{
  int x1, y1, x2, y2;
  rect() {}
  rect(int a, int b, int c, int d) : x1(a), y1(b), x2(c), y2(d) {}
  bool in_x(int x) const { return x1 < x && x < x2; }
  bool in_y(int y) const { return y1 < y && y < y2; }
  bool has_common(const rect& r) const
  {
    return !(x2 <= r.x1 || r.x2 <= x1 || y2 <= r.y1 || r.y2 <= y1);
  }
};

bool check(int W, int H, int N, const rect *rs, const rect& r)
{
  if (r.x2 > W || r.y2 > H) {
    return false;
  }
  for (int i = 0; i < N; i++) {
    if (rs[i].has_common(r)) {
      return false;
    }
  }
  return true;
}

int main()
{
  int T;
  scanf("%d", &T);
  while (T-- > 0) {
    int N, W, H;
    scanf("%d %d %d", &N, &W, &H);
    static rect rs[1000];
    static int xs[1001], ys[1001];
    for (int i = 0; i < N; i++) {
      scanf("%d %d %d %d", &rs[i].x1, &rs[i].y1, &rs[i].x2, &rs[i].y2);
      xs[i] = rs[i].x2;
      ys[i] = rs[i].y2;
    }
    xs[N] = ys[N] = 0;
    int w, h;
    scanf("%d %d", &w, &h);
    sort(xs, xs+N+1);
    sort(ys, ys+N+1);
    for (int i = 0; i <= N; i++) {
      for (int j = 0; j <= N; j++) {
        if (check(W, H, N, rs, rect(xs[j], ys[i], xs[j]+w, ys[i]+h))) {
          printf("%d %d\n", xs[j], ys[i]);
          goto FINISH;
        }
      }
    }
    puts("Fail!");
FINISH:
    ;
  }
  return 0;
}
