#include <cstdio>
#include <vector>
#include <complex>
using namespace std;
typedef complex<double> P;

struct circle/*{{{*/
{
  P o;
  double r;
  circle() {}
  circle(const P& p, double x) : o(p), r(x) {}

  // POJ 1418 Viva Confetti
  // POJ 2149 Inherit the Spheres
  inline bool intersects(const circle& c) const
  {
    return !contains(c) && !c.contains(*this) && abs(o - c.o) <= r + c.r;
  }

  inline bool contains(const circle& c) const
  {
    return abs(o - c.o)+c.r <= r;
  }
};/*}}}*/

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

  int size(int x) { return -parent[root(x)]; }
};/*}}}*/

int main()
{
  int N;
  while (scanf("%d", &N) != EOF && N != -1) {
    vector<circle> cs;
    DisjointSet s(N);
    for (int i = 0; i < N; i++) {
      double x, y, r;
      scanf("%lf %lf %lf", &x, &y, &r);
      circle c(P(x, y), r);
      for (int j = 0; j < i; j++) {
        if (cs[j].contains(c) || cs[j].intersects(c)) {
          s.unite(i, j);
        }
      }
      cs.push_back(c);
    }
    int ans = 1;
    for (int i = 0; i < N; i++) {
      ans = max(ans, s.size(i));
    }
    printf("The largest component contains %d rings\n", ans);
  }
  return 0;
}
