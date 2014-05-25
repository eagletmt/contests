#include <iostream>
#include <cstdio>
#include <vector>
#include <queue>
#include <map>
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

    bool find(int x, int y)
    {
      return root(x) == root(y);
    }

    int size(int x)
    {
      return -parent[root(x)];
    }
};/*}}}*/

struct edge {/*{{{*/
  int u, v;
  typedef double weight_type;
  weight_type w;
  edge(int s, int d, weight_type w_) : u(s), v(d), w(w_) {}
  bool operator<(const edge& rhs) const
  {
    return w > rhs.w;
  }
};/*}}}*/

template <class Edge>
typename Edge::weight_type kruskal(priority_queue<Edge> edges, const int N)/*{{{*/
{
  DisjointSet s(N);
  typename Edge::weight_type ttl = 0;
  while (s.size(0) < N && !edges.empty()) {
    const Edge e = edges.top();
    edges.pop();
    if (s.unite(e.u, e.v)) {
      ttl += e.w;
    }
  }
  return ttl;
}/*}}}*/

int main()
{
  double L;
  cin >> L;
  int N;
  cin >> N;
  map<string,int> m;
  for (int i = 0; i < N; i++) {
    string name;
    cin >> name;
    m.insert(make_pair(name, i));
  }
  int M;
  cin >> M;
  priority_queue<edge> edges;
  for (int i = 0; i < M; i++) {
    string src, dst;
    double c;
    cin >> src >> dst >> c;
    const int s = m[src];
    const int d = m[dst];
    edges.push(edge(s, d, c));
  }

  const double r = kruskal(edges, N);
  if (r <= L) {
    printf("Need %.1f miles of cable\n", r);
  } else {
    puts("Not enough cable");
  }
  return 0;
}
