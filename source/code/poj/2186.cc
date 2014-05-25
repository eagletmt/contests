#include <cstdio>
#include <vector>
#include <stack>
using namespace std;

void scc_visit(const vector<vector<int> >& g, int v, vector<int>& scc_map, int& scc_size,/*{{{*/
    stack<int>& stk, vector<bool>& in_stk, vector<int>& low, vector<int>& num, int& time)
{
  low[v] = num[v] = ++time;
  stk.push(v);
  in_stk[v] = true;
  for (vector<int>::const_iterator it(g[v].begin()); it != g[v].end(); ++it) {
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

pair<vector<int>,int> strongly_connected_components(const vector<vector<int> >& g)/*{{{*/
{
  const int N = g.size();
  vector<int> num(N), low(N);
  stack<int> stk;
  vector<bool> in_stk(N, false);
  int time = 0;
  vector<int> scc_map(N);
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
  scanf("%d %d\n", &N, &M);
  vector<vector<int> > g(N);
  for (int i = 0; i < M; i++) {
    int a, b;
    scanf("%d %d\n", &a, &b);
    --a;  --b;
    g[a].push_back(b);
  }
  const pair<vector<int>,int> r = strongly_connected_components(g);
  vector<bool> refers_scc(r.second, false);
  for (int i = 0; i < N; i++) {
    for (vector<int>::const_iterator it(g[i].begin()); it != g[i].end(); ++it) {
      if (r.first[i] != r.first[*it]) {
        refers_scc[r.first[i]] = true;
      }
    }
  }
  int not_refer = 0;
  for (int i = 0; i < r.second; i++) {
    if (!refers_scc[i]) {
      ++not_refer;
    }
  }
  if (not_refer > 1) {
    puts("0");
  } else {
    int ans = 0;
    for (int i = 0; i < N; i++) {
      if (!refers_scc[r.first[i]]) {
        ++ans;
      }
    }
    printf("%d\n", ans);
  }
  return 0;
}
