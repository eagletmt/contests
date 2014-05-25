#include <cstdio>
#include <stack>
using namespace std;

int main()
{
  int N;
  while (scanf("%d", &N) != EOF && N != -1) {
    stack<pair<int,int> > stk;
    int prev_h = -1;
    int ans = 0;
    for (int i = 0; i < N; i++) {
      int w, h;
      scanf("%d %d", &w, &h);
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
    printf("%d\n", ans);
  }
  return 0;
}
