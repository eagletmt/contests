#include <iostream>
#include <sstream>
#include <vector>
#include <algorithm>
using namespace std;
static const int INF = 10000000;

struct edge
{
  int u, v, cost, len;
  edge(int a, int b, int c, int d)
    : u(a), v(b), cost(c), len(d)
  {}
  bool operator<(const edge& e) const { return cost < e.cost; }
};

void dfs(int n, const vector<edge>& es, vector<int>& reachable)
{
  reachable[n] = true;
  for (vector<edge>::const_iterator it = es.begin(); it != es.end(); ++it) {
    if (it->v == n && !reachable[it->u]) {
      dfs(it->u, es, reachable);
    }
  }
}

int main()
{
  ios::sync_with_stdio(false);
  int N;
  while (cin >> N) {
    int M, A, B;
    cin >> M >> A >> B;
    vector<vector<edge> > g(N);
    vector<int> gm(N, INF);
    for (int i = 0; i < M; i++) {
      string s;
      cin >> s;
      stringstream ss;
      for (string::const_iterator it = s.begin(); it != s.end(); ++it) {
        switch (*it) {
          case '(':
          case ',':
          case '[':
          case ']':
          case ')':
            ss << ' ';  break;
          default:
            ss << *it;  break;
        }
      }
      int u, v, uv, l, vu;
      ss >> u >> v >> uv >> l >> vu;
      gm[u] = min(gm[u], uv);
      gm[v] = min(gm[v], vu);
      g[u].push_back(edge(u, v, uv, l));
      g[v].push_back(edge(v, u, vu, l));
    }

    vector<edge> es;
    for (int n = 0; n < N; n++) {
      if (!g[n].empty()) {
        for (vector<edge>::const_iterator it = g[n].begin(); it != g[n].end(); ++it) {
          if (it->cost == gm[n]) {
            es.push_back(*it);
          }
        }
      }
    }

    vector<int> reachable(N, false);
    dfs(B, es, reachable);
    if (!reachable[A]) {
      cout << "VOID" << endl;
      continue;
    }

    vector<int> cs(N, INF), ls(N, INF);
    cs[A] = ls[A] = 0;
    bool updated = true;
    for (int i = 0; updated && i <= N; i++) {
      updated = false;
      for (vector<edge>::const_iterator it = es.begin(); it != es.end(); ++it) {
        if (!reachable[it->v] || cs[it->u] == INF) {
          continue;
        }
        const int c = cs[it->u] + it->cost;
        const int l = ls[it->u] + it->len;
        if (c < cs[it->v] || (c == cs[it->v] && l < ls[it->v])) {
          cs[it->v] = c;
          ls[it->v] = ls[it->u] + it->len;
          updated = true;
        }
      }
    }

    if (updated) {
      cout << "UNBOUND" << endl;
    } else {
      cout << cs[B] << ' ' << ls[B] << endl;
    }
  }
  return 0;
}
