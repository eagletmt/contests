#include <iostream>
#include <vector>
#include <queue>
using namespace std;

class DisjointSet {
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
    DisjointSet(int size) : parent(size, -1) {}

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
};

struct Edge {
  int from, to, weight;
  Edge(int f, int t, int w) : from(f), to(t), weight(w) {}
  
  bool operator<(const Edge& e) const
  {
    return weight > e.weight;
  }
};

int kruskal(priority_queue<Edge> edges, const int N)
{
  DisjointSet s(N);
  int ttl = 0;
  while (s.size(0) < N) {
    const Edge e = edges.top();
    edges.pop();
    if (s.unite(e.from, e.to)) {
      ttl += e.weight;
    }
  }
  return ttl;
}

int main(void)
{
  int N;
  while (cin >> N) {
    priority_queue<Edge> edges;
    for (int i = 0; i < N; i++) {
      for (int j = 0; j < N; j++) {
        int w;
        cin >> w;
        edges.push(Edge(i, j, w));
      }
    }
    cout << kruskal(edges, N) << endl;
  }
}
