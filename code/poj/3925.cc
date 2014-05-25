#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>
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

int main()
{
  int n, m;
  while (cin >> n >> m && n != 0) {
    vector<int> weights(n);
    for (int i = 0; i < n; i++) {
      cin >> weights[i];
    }
    vector<edge> edges;
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < n; j++) {
        int w;
        cin >> w;
        if (i < j) {
          edges.push_back(edge(i, j, w));
        }
      }
    }
    sort(edges.begin(), edges.end());

    vector<bool> use(n, false);
    for (int i = 0; i < m; i++) {
      use[i] = true;
    }
    sort(use.begin(), use.end());
    int min_ew = 0, min_nw = 0;
    vector<int> ans;
    do {
      int nw = 0;
      vector<int> nodes;
      for (int i = 0; i < n; i++) {
        if (use[i]) {
          nw += weights[i];
          nodes.push_back(i+1);
        }
      }

      // kruskal
      DisjointSet s(n);
      int ew = 0;
      for (vector<edge>::const_iterator it(edges.begin()); it != edges.end(); ++it) {
        if (use[it->u] && use[it->v] && s.unite(it->u, it->v)) {
          ew += it->w;
          if (s.size(it->u) == m) {
            if (min_nw == 0 || ew*min_nw <= min_ew*nw) {
              min_ew = ew;
              min_nw = nw;
              ans = nodes;
            }
            break;
          }
        }
      }
    } while (next_permutation(use.begin(), use.end()));
    copy(ans.begin(), ans.end(), ostream_iterator<int>(cout, " "));
    cout << endl;
  }
  return 0;
}
