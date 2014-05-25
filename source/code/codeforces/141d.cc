#include <iostream>
#include <vector>
#include <map>
#include <queue>
#include <algorithm>
using namespace std;

struct ramp { int id, x, d, t, p; };
struct edge
{
  int id, to;
  long long cost;
  edge(int i, int t, long long c) : id(i), to(t), cost(c) {}
  bool operator<(const edge& e) const { return cost > e.cost; }
};

int main()
{
  ios::sync_with_stdio(false);
  int N, L;
  cin >> N >> L;
  vector<ramp> rs;
  vector<int> xs;
  for (int i = 0; i < N; i++) {
    ramp r;
    r.id = i+1;
    cin >> r.x >> r.d >> r.t >> r.p;
    if (r.x-r.p >= 0 && r.t < r.d) {
      rs.push_back(r);
      xs.push_back(r.x - r.p);
      xs.push_back(r.x + r.d);
    }
  }
  xs.push_back(0);
  xs.push_back(L);
  sort(xs.begin(), xs.end());
  xs.erase(unique(xs.begin(), xs.end()), xs.end());
  const int M = xs.size();

  vector<vector<edge> > g(M);
  map<int,int> x_inv;
  for (int i = 0; i < M; i++) {
    x_inv[xs[i]] = i;
  }
  for (int i = 0; i < M-1; i++) {
    g[i].push_back(edge(-1, i+1, xs[i+1] - xs[i]));
    g[i+1].push_back(edge(-1, i, xs[i+1] - xs[i]));
  }
  for (vector<ramp>::const_iterator it = rs.begin(); it != rs.end(); ++it) {
    if (!x_inv.count(it->x - it->p) || !x_inv.count(it->x + it->d)) {
      throw "x_inv";
    }
    const int u = x_inv[it->x - it->p];
    const int v = x_inv[it->x + it->d];
    g[u].push_back(edge(it->id, v, it->p + it->t));
  }

  vector<long long> dist(M, 1LL<<40);
  priority_queue<pair<long long,int> > q;
  dist[0] = 0;
  q.push(make_pair(0, 0));

  vector<pair<int,int> > pre(M);
  pre[0].second = -1;
  while (!q.empty()) {
    const int n = q.top().second;
    const long long c = -q.top().first;
    q.pop();
    if (n == M-1) {
      break;
    }
    if (dist[n] < c) {
      continue;
    }
    for (vector<edge>::const_iterator it = g[n].begin(); it != g[n].end(); ++it) {
      const int m = it->to;
      const long long cc = c + it->cost;
      if (cc < dist[m]) {
        dist[m] = cc;
        pre[m] = make_pair(it->id, n);
        q.push(make_pair(-cc, m));
      }
    }
  }
  cout << dist[M-1] << endl;
  vector<int> t;
  for (int n = M-1; n != -1; n = pre[n].second) {
    const int id = pre[n].first;
    if (id > 0) {
      t.push_back(id);
    }
  }
  cout << t.size() << endl;
  for (vector<int>::const_reverse_iterator it = t.rbegin(); it != t.rend(); ++it) {
    if (it != t.rbegin()) {
      cout << ' ';
    }
    cout << *it;
  }
  cout << endl;
  return 0;
}
