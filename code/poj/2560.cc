#include <cstdio>
#include <vector>
#include <complex>
#include <algorithm>
using namespace std;
typedef complex<double> P;

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
  typedef double weight_type;
  weight_type w;
  edge(int s, int d, weight_type w_) : u(s), v(d), w(w_) {}
  bool operator<(const edge& that) const { return w < that.w; }
};/*}}}*/

template <class Edge>
typename Edge::weight_type kruskal(const vector<Edge>& edges, int N)/*{{{*/
{
  DisjointSet s(N);
  typename Edge::weight_type ttl = 0;
  for (typename vector<Edge>::const_iterator it = edges.begin(); s.size(0) < N && it != edges.end(); ++it) {
    if (s.unite(it->u, it->v)) {
      ttl += it->w;
    }
  }
  return ttl;
}/*}}}*/

int main()
{
  int N;
  scanf("%d", &N);
  vector<P> ps;
  for (int i = 0; i < N; i++) {
    double x, y;
    scanf("%lf %lf", &x, &y);
    ps.push_back(P(x, y));
  }
  vector<edge> edges;
  for (int i = 0; i < N; i++) {
    for (int j = i+1; j < N; j++) {
      const double d = abs(ps[i] - ps[j]);
      edges.push_back(edge(i, j, d));
      edges.push_back(edge(j, i, d));
    }
  }
  sort(edges.begin(), edges.end());

  printf("%.2f\n", kruskal(edges, N));
  return 0;
}
