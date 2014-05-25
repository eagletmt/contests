#include <cstdio>
#include <algorithm>
using namespace std;

pair<int,int> parse(const char *buf)
{
  int x, y;
  sscanf(buf, "%d %d", &x, &y);
  return make_pair(x, y);
}

int gcd(int x, int y)
{
  if (x <= y) {
    swap(x, y);
  }
  if (y == 0) {
    return x;
  }
  int r;
  while ((r = x % y) != 0) {
    x = y;
    y = r;
  }
  return y;
}

int main()
{
  char buf[80];
  int Ti = 0;
  while (fgets(buf, sizeof buf, stdin) && !(buf[0] == '-' && buf[1] == '-')) {
    static pair<int,int> ps[1000];
    ps[0] = parse(buf);
    int N = 1;
    while (fgets(buf, sizeof buf, stdin) && !(buf[0] == '-' && buf[1] == '-')) {
      ps[N++] = parse(buf);
    }

    int ans = 0;
    for (int i = 0; i < N; i++) {
      static long long m[1000];
      for (int j = i+1; j < N; j++) {
        int dx = ps[j].first - ps[i].first;
        int dy = ps[j].second - ps[i].second;
        if (dx < 0) {
          dx = -dx;
          dy = -dy;
        }
        int g = gcd(dx, dy);
        m[j] = (dx/g + 1000000L)*2000000LL + dy/g;
      }
      sort(m+i+1, m+N);
      for (int j = i+1; j < N;) {
        int k = j;
        while (k < N && m[k] == m[j]) {
          ++k;
        }
        ans = max(ans, k - j + 1);
        j = k;
      }
    }
    printf("%d. %d\n", ++Ti, ans);
  }
  return 0;
}
