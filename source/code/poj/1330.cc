#include <cstdio>
#include <vector>
using namespace std;

class DisjointSet { // {{{
  private:
    vector<int> parent;

  public:
    DisjointSet(int s) : parent(s, -1) {}

    int root(int x)
    {
      if (parent[x] < 0) {
        return x;
      } else {
        parent[x] = root(parent[x]);
        return parent[x];
      }
    }


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
};  // }}}

void tarjan_visit(const vector<vector<int> >& g, int u, int x, int y, vector<bool>& color, vector<int>& ancestor, DisjointSet& s, int& ans)
{
  ancestor[s.root(u)] = u;
  for (vector<int>::const_iterator it(g[u].begin()); it != g[u].end(); ++it) {
    tarjan_visit(g, *it, x, y, color, ancestor, s, ans);
    s.unite(u, *it);
    ancestor[s.root(u)] = u;
  }
  color[u] = true;
  int w = -1;
  if (u == x) {
    w = y;
  } else if (u == y) {
    w = x;
  }
  if (w != -1 && color[w]) {
    ans = ancestor[s.root(w)];
  }
}

int tarjan(const vector<vector<int> >& g, int root, int x, int y)
{
  DisjointSet s(g.size());
  vector<bool> color(g.size());
  vector<int> ancestor(g.size());
  int ans;
  tarjan_visit(g, root, x, y, color, ancestor, s, ans);
  return ans;
}

int main()
{
  int T;
  scanf("%d", &T);
  while (T-- > 0) {
    int N;
    scanf("%d", &N);
    vector<vector<int> > g(N);
    vector<int> deg(N, 0);
    for (int i = 0; i < N-1; i++) {
      int u, v;
      scanf("%d %d", &u, &v);
      --u;  --v;
      g[u].push_back(v);
      ++deg[v];
    }
    int root = -1;
    for (int i = 0; i < N; i++) {
      if (deg[i] == 0) {
        root = i;
      }
    }

    int x, y;
    scanf("%d %d", &x, &y);
    --x;  --y;
    printf("%d\n", tarjan(g, root, x, y)+1);
  }
  return 0;
}
