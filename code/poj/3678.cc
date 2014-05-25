#include <cstdio>
#include <string>
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

// 2-SAT
int main()
{
  int N, M;
  scanf("%d %d", &N, &M);
  vector<vector<int> > g(2*N);
  for (int i = 0; i < M; i++) {
    int a, b, c;
    char o[16];
    scanf("%d %d %d %s", &a, &b, &c, o);
    const string op(o);
    if (op == "AND") {
      if (c) {
        // a && b = 1 == (!a -> a) && (!b -> b)
        g[a+N].push_back(a);
        g[b+N].push_back(b);
      } else {
        // a && b = 0 == (a -> !b) && (b -> !a)
        g[a].push_back(b+N);
        g[b].push_back(a+N);
      }
    } else if (op == "OR") {
      if (c) {
        // a || b = 1 == (!a -> b) && (!b -> a)
        g[a+N].push_back(b);
        g[b+N].push_back(a);
      } else {
        // a || b = 0 == (a -> !a) && (b -> !b)
        g[a].push_back(a+N);
        g[b].push_back(b+N);
      }
    } else {
      // XOR
      if (c) {
        // a ^ b = 1 == (a -> !b) && (b -> !a) && (!a -> b) && (!b -> a)
        g[a].push_back(b+N);
        g[b].push_back(a+N);
        g[a+N].push_back(b);
        g[b+N].push_back(a);
      } else {
        // a ^ b = 0 == (a -> b) && (b -> a) && (!a -> !b) && (!b -> !a)
        g[a].push_back(b);
        g[b].push_back(a);
        g[a+N].push_back(b+N);
        g[b+N].push_back(a+N);
      }
    }
  }

  const pair<vector<int>, int> p = strongly_connected_components(g);
  vector<vector<bool> > has(p.second, vector<bool>(N, false));
  for (int i = 0; i < N; i++) {
    has[p.first[i]][i] = true;
  }
  for (int i = N; i < 2*N; i++) {
    if (has[p.first[i]][i-N]) {
      puts("NO");
      return 0;
    }
  }
  puts("YES");
  return 0;
}
