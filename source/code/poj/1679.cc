#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class DisjointSet/*{{{*/
{
  private:
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

  public:
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
  typedef int weight_type;
  weight_type w;
  edge(int s, int d, weight_type w_) : u(s), v(d), w(w_) {}
  bool operator<(const edge& that) const { return w < that.w; }
};/*}}}*/

int solve(const vector<edge>& edges, int N)
{
  const int M = edges.size();
  int ans = 0;
  vector<int> used_edges;
  {
    DisjointSet s(N);
    for (int i = 0; i < M; i++) {
      if (s.unite(edges[i].u, edges[i].v)) {
        ans += edges[i].w;
        used_edges.push_back(i);
      }
    }
  }

  for (vector<int>::const_iterator it(used_edges.begin()); it != used_edges.end(); ++it) {
    DisjointSet s(N);
    int c = 0;
    int n = 1;
    for (int i = 0; i < M; i++) {
      if (i == *it) {
        continue;
      }
      if (s.unite(edges[i].u, edges[i].v)) {
        c += edges[i].w;
        ++n;
      }
    }
    if (n == N && c == ans) {
      return -1;
    }
  }
  return ans;
}

int main()
{
  int T;
  cin >> T;
  while (T-- > 0) {
    int N, M;
    cin >> N >> M;
    vector<edge> edges;
    for (int i = 0; i < M; i++) {
      int u, v, w;
      cin >> u >> v >> w;
      --u;  --v;
      edges.push_back(edge(u, v, w));
    }
    sort(edges.begin(), edges.end());

    const int ans = solve(edges, N);
    if (ans == -1) {
      cout << "Not Unique!" << endl;
    } else {
      cout << ans << endl;
    }
  }
  return 0;
}
