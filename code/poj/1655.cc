#include <cstdio>
#include <algorithm>
using namespace std;
static const int M = 20000;

int ans;
int ans_min = M;

int dfs(const pair<int,int> *edges, const int *begins, int N, int n, int parent)
{
  int c = 1;
  int m = 0;
  for (int i = begins[n]; i < begins[n+1]; i++) {
    const int *it = &edges[i].second;
    if (*it != parent) {
      const int x = dfs(edges, begins, N, *it, n);
      c += x;
      m = max(m, x);
    }
  }
  m = max(m, N - c);
  if (ans_min == m) {
    ans = min(ans, n);
  } else if (m < ans_min) {
    ans_min = m;
    ans = n;
  }
  return c;
}

int main()
{
  int T;
  scanf("%d", &T);
  while (T-- > 0) {
    int N;
    scanf("%d", &N);
    static pair<int,int> edges[2*M];
    for (int i = 0; i < N-1; i++) {
      int u, v;
      scanf("%d %d", &u, &v);
      --u;  --v;
      edges[2*i].first = edges[2*i+1].second = u;
      edges[2*i].second = edges[2*i+1].first = v;
    }
    sort(edges, edges+2*(N-1));
    static int begins[M];
    begins[edges[0].first] = 0;
    for (int i = 1; i < 2*(N-1); i++) {
      if (edges[i].first != edges[i-1].first) {
        begins[edges[i].first] = i;
      }
    }
    begins[N] = 2*(N-1);

    ans = N;
    ans_min = N;
    dfs(edges, begins, N, 0, -1);
    printf("%d %d\n", ans+1, ans_min);
  }
  return 0;
}
