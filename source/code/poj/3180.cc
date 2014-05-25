#include <cstdio>
#include <vector>
#include <stack>
using namespace std;

void scc_visit(const vector<int> *g, int v, int *scc_map, int& scc_size,/*{{{*/
        stack<int>& stk, bool *in_stk, int *low, int *num, int& time)
{
  low[v] = num[v] = ++time;
  stk.push(v);
  in_stk[v] = true;
  for (vector<int>::const_iterator it = g[v].begin(); it != g[v].end(); ++it) {
    const int u = *it;
    if (num[u] == 0) {
      scc_visit(g, u, scc_map, scc_size, stk, in_stk, low, num, time);
      low[v] = min(low[v], low[u]);
    } else if (in_stk[u]) {
      low[v] = min(low[v], num[u]);
    }
  }
  if (low[v] == num[v]) {
    for (;;) {
      const int u = stk.top();
      stk.pop();
      in_stk[u] = false;
      scc_map[u] = scc_size;
      if (u == v) {
        break;
      }
    }
    ++scc_size;
  }
}/*}}}*/

pair<int*,int> strongly_connected_components(const vector<int> *g, int N)/*{{{*/
{
  static int num[10000], low[10000];
  stack<int> stk;
  static bool in_stk[10000];
  int time = 0;
  static int scc_map[10000];
  int scc_size = 0;
  for (int v = 0; v < N; v++) {
    if (num[v] == 0) {
      scc_visit(g, v, scc_map, scc_size, stk, in_stk, low, num, time);
    }
  }
  return make_pair(scc_map, scc_size);
}/*}}}*/

int main()
{
  int N, M;
  scanf("%d %d", &N, &M);
  static vector<int> g[10000];
  for (int i = 0; i < M; i++) {
    int u, v;
    scanf("%d %d", &u, &v);
    --u;  --v;
    g[u].push_back(v);
  }

  const pair<int*,int> r = strongly_connected_components(g, N);
  static int cnt[10000];
  for (int i = 0; i < N; i++) {
    ++cnt[r.first[i]];
  }
  int ans = 0;
  for (int i = 0; i < r.second; i++) {
    if (cnt[i] != 1) {
      ++ans;
    }
  }
  printf("%d\n", ans);
  return 0;
}
