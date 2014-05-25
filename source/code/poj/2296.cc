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

// O(V+E)
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
bool sat(const vector<vector<int> >& g)
{
  const pair<vector<int>, int> p = strongly_connected_components(g);
  const int N = g.size()/2;
  vector<vector<int> > has(p.second, vector<int>(N, false));
  for (int i = 0; i < N; i++) {
    has[p.first[i]][i] = true;
  }
  for (int i = N; i < 2*N; i++) {
    if (has[p.first[i]][i-N]) {
      return false;
    }
  }
  return true;
}

struct rect
{
  double left, right, below, above;
  rect(double a, double b, double c, double d)
    : left(a), right(b), below(c), above(d) {}

  bool intersects(const rect& r) const
  {
    if (right <= r.left) {
      return false;
    }
    if (r.right <= left) {
      return false;
    }
    if (above <= r.below) {
      return false;
    }
    if (r.above <= below) {
      return false;
    }
    return true;
  }
};

bool ok(int size, const vector<pair<int,int> >& v)
{
  const int N = v.size();
  vector<rect> rs;
  for (vector<pair<int,int> >::const_iterator it = v.begin(); it != v.end(); ++it) {
    rs.push_back(rect(it->first - size/2.0, it->first + size/2.0, it->second, it->second + size));
    rs.push_back(rect(it->first - size/2.0, it->first + size/2.0, it->second - size, it->second));
  }

  vector<vector<int> > g(4*N);
  for (int i = 0; i < N; i++) {
    g[2*i+2*N].push_back(2*i+1);
    g[2*i+1+2*N].push_back(2*i);
  }
  for (int i = 0; i < N; i++) {
    for (int j = i+1; j < N; j++) {
      for (int k = 0; k < 4; k++) {
        static const int di[] = {0, 0, 1, 1}, dj[] = {0, 1, 0, 1};
        const int s = 2*i + di[k], t = 2*j + dj[k];
        if (rs[s].intersects(rs[t])) {
          g[s].push_back(t+2*N);
          g[t].push_back(s+2*N);
        }
      }
    }
  }
  return sat(g);
}

int main()
{
  int T;
  scanf("%d", &T);
  while (T-- > 0) {
    int N;
    scanf("%d", &N);
    vector<pair<int,int> > v(N);
    for (int i = 0; i < N; i++) {
      scanf("%d %d", &v[i].first, &v[i].second);
    }

    int lo = 1, hi = 100000;
    while (lo < hi) {
      const int mid = (lo + hi + 1)/2;
      if (ok(mid, v)) {
        lo = mid;
      } else {
        hi = mid-1;
      }
    }
    printf("%d\n", lo);
  }
  return 0;
}
