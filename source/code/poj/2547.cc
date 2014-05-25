#include <cstdio>
using namespace std;

struct package { int x, w; };
int N, W;
package ps[20];
int ans[20];

bool ok(unsigned s)
{
  double left = 1.5 * W, right = -1.5 * W;
  for (int i = 0; i < N; i++) {
    if (s & (1<<i)) {
      left += ps[i].w * (ps[i].x + 1.5);
      right += ps[i].w * (ps[i].x - 1.5);
    }
  }
  return left >= 0.0 && right <= 0.0;
}

bool valid[1<<20];
int memo[1<<20];

bool dfs(unsigned s, int n)
{
  if (memo[s] != -1) {
    return memo[s];
  }
  if (s == 0) {
    return true;
  } else {
    for (int i = 0; i < N; i++) {
      if (ans[i] == -1) {
        const unsigned t = s & ~(1<<i);
        ans[i] = n;
        if (valid[t] && dfs(t, n+1)) {
          return (memo[s] = true);
        }
        ans[i] = -1;
      }
    }
    return (memo[s] = false);
  }
}

int main()
{
  int L;
  for (int Ti = 1; scanf("%d %d %d", &L, &W, &N) != EOF && L != 0; Ti++) {
    printf("Case %d:\n", Ti);
    for (int i = 0; i < N; i++) {
      scanf("%d %d", &ps[i].x, &ps[i].w);
      ans[i] = -1;
    }

    for (unsigned s = 0; s < (1<<N); s++) {
      valid[s] = ok(s);
      memo[s] = -1;
    }

    if (dfs((1<<N)-1, 0)) {
      package qs[20];
      for (int i = 0; i < N; i++) {
        qs[ans[i]] = ps[i];
      }
      for (int i = 0; i < N; i++) {
        printf("%d %d\n", qs[i].x, qs[i].w);
      }
    } else {
      puts("Impossible");
    }
  }
  return 0;
}
