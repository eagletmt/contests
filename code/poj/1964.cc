#include <cstdio>
#include <stack>
#include <algorithm>
using namespace std;

int max_rect(const int *hist, int N)
{
  stack<pair<int,int> > stk;
  int prev_h = -1;
  int ans = 0;
  for (int i = 0; i < N; i++) {
    const int w = 1, h = hist[i];
    if (h >= prev_h) {
      stk.push(make_pair(w, h));
    } else {
      int width = 0;
      while (!stk.empty() && stk.top().second > h) {
        width += stk.top().first;
        ans = max(ans, width * stk.top().second);
        stk.pop();
      }
      width += w;
      stk.push(make_pair(width, h));
    }
    prev_h = h;
  }
  for (int width = 0; !stk.empty(); stk.pop()) {
    width += stk.top().first;
    ans = max(ans, width * stk.top().second);
  }
  return ans;
}

int main()
{
  int T;
  scanf("%d", &T);
  while (T-- > 0) {
    int H, W;
    scanf("%d %d", &H, &W);
    static int hist[1000+1][1000];
    for (int i = 1; i <= H; i++) {
      for (int j = 0; j < W; j++) {
        char buf[4];
        scanf("%s", buf);
        if (*buf == 'F') {
          hist[i][j] = hist[i-1][j] + 1;
        } else {
          hist[i][j] = 0;
        }
      }
    }
    int ans = 0;
    for (int i = 1; i <= H; i++) {
      ans = max(ans, max_rect(hist[i], W));
    }
    printf("%d\n", ans*3);
  }
  return 0;
}
