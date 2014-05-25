#include <iostream>
#include <vector>
#include <map>
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

struct edge {
  int u, v;
  int w;
  edge(int s, int d, int w_) : u(s), v(d), w(w_) {}
  bool operator<(const edge& that) const { return w < that.w; }
};

int kruskal(const vector<edge>& edges, const int N, const vector<int>& avail)
{
  DisjointSet s(N);
  int ttl = 0;
  const int M = edges.size();
  for (int i = 0; i < M && s.size(0) < N; i++) {
    if (avail[i] && s.unite(edges[i].u, edges[i].v)) {
      ttl += edges[i].w;
    }
  }
  if (s.size(0) == N) {
    return ttl;
  } else {
    return 10000000;
  }
}

int numbering(map<string,int>& m, const string& name)
{
  const map<string,int>::const_iterator it = m.find(name);
  if (it == m.end()) {
    const int n = m.size();
    m.insert(make_pair(name, n));
    return n;
  } else {
    return it->second;
  }
}

int main()
{
  int M;
  cin >> M;
  map<string, int> m;
  vector<edge> edges;
  for (int i = 0; i < M; i++) {
    string s1, s2;
    int w;
    cin >> s1 >> s2 >> w;
    const int u = numbering(m, s1);
    const int v = numbering(m, s2);
    edges.push_back(edge(u, v, w));
  }
  sort(edges.begin(), edges.end());
  const int N = m.size();
  int K;
  cin >> K;

  const int root = m["Park"];
  vector<int> v;
  for (int i = 0; i < M; i++) {
    if (edges[i].u == root || edges[i].v == root) {
      v.push_back(i);
    }
  }
  const int size = v.size();

  vector<int> avail(M, 1);
  vector<int> a(size, 0);
  for (int i = 0; i < min(size, K); i++) {
    a[i] = 1;
  }
  sort(a.begin(), a.end());
  int ans = 10000000;
  do {
    for (int i = 0; i < size; i++) {
      avail[v[i]] = a[i];
    }
    ans = min(ans, kruskal(edges, N, avail));
  } while (next_permutation(a.begin(), a.end()));

  cout << "Total miles driven: " << ans << endl;
  return 0;
}
