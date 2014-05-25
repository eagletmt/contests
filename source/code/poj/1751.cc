#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
using namespace std;

struct DisjointSet/*{{{*/
{
  vector<int> parent;

  int root(int x)
  {
    if (parent[x] < 0) {
      return x;
    } else {
      parent[x] = root(parent[x]);
      return parent[x];
    }
  }

  explicit DisjointSet(int n) : parent(n, -1) {}

  bool unite(int x, int y)
  {
    const int a = root(x);
    const int b = root(y);
    if (a != b) {
      if (parent[a] < parent[b]) {
        parent[a] += parent[b];
        parent[b] = a;
      } else {
        parent[b] += parent[a];
        parent[a] = b;
      }
      return true;
    } else {
      return false;
    }
  }

  bool find(int x, int y) { return root(x) == root(y); }
  int size(int x) { return -parent[root(x)]; }
};/*}}}*/

struct edge {/*{{{*/
  int u, v;
  typedef double weight_type;
  weight_type w;
  edge(int s, int d, weight_type w_) : u(s), v(d), w(w_) {}
  bool operator<(const edge& that) const { return w < that.w; }
};/*}}}*/

template <class Edge>
vector<Edge> kruskal(const vector<Edge>& edges, DisjointSet& s)/*{{{*/
{
  // assert(is_sorted(edges.begin(), edges.end()))
  const int N = s.parent.size();
  vector<Edge> ans;
  for (typename vector<Edge>::const_iterator it = edges.begin(); s.size(0) < N && it != edges.end(); ++it) {
    if (s.unite(it->u, it->v)) {
      ans.push_back(*it);
    }
  }
  return ans;
}/*}}}*/

inline double dist(const pair<int,int>& p, const pair<int,int>& q)
{
  const double x = p.first - q.first;
  const double y = p.second - q.second;
  return sqrt(x*x + y*y);
}

int main()
{
  int N;
  cin >> N;
  vector<pair<int,int> > towns(N);
  for (int i = 0; i < N; i++) {
    cin >> towns[i].first >> towns[i].second;
  }
  int M;
  cin >> M;
  DisjointSet s(N);
  for (int i = 0; i < M; i++) {
    int u, v;
    cin >> u >> v;
    --u;  --v;
    s.unite(u, v);
  }

  vector<edge> es;
  for (int i = 0; i < N; i++) {
    for (int j = i+1; j < N; j++) {
      if (!s.find(i, j)) {
        es.push_back(edge(i, j, dist(towns[i], towns[j])));
      }
    }
  }
  sort(es.begin(), es.end());
  const vector<edge> ans = kruskal(es, s);
  for (vector<edge>::const_iterator it = ans.begin(); it != ans.end(); ++it) {
    cout << it->u+1 << " " << it->v+1 << endl;
  }
  return 0;
}
