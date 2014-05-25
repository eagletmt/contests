#include <cstdio>
#include <vector>
#include <algorithm>
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

int extgcd(int x, int y, int& a, int& b)
{
  if (x < y) {
    return extgcd(y, x, b, a);
  }
  a = 1;
  int aa = 0;
  b = 0;
  int bb = 1;
  while (y > 0) {
    const int r = x % y;
    const int q = x / y;
    x = y; y = r;
    const int t = a - q*aa;
    const int u = b - q*bb;
    a = aa;  aa = t;
    b = bb;  bb = u;
  }
  return x;
}

int solve(int x0, int y0, int x1, int y1)
{
  int a, b;
  const int g = extgcd(x0, x1, a, b);
  if (a < 0) {
    swap(a, b);
    swap(x0, x1);
    swap(y0, y1);
  }
  int y = y1 - y0;
  if (y % g != 0) {
    return -1;
  }
  if (y < 0) {
    y = -y;
    a -= x1;
    b += x0;
    a = -a;
  } else if (y > 0) {
    b = -b;
  }
  const long long q = y / g;
  const long long s = a*q;
  const long long t = b*q;
  const long long z = min(s/x1, t/x0);
  return x0 * (s-x1*z);
}

int main()
{
  int T;
  scanf("%d", &T);
  while (T-- > 0) {
    long long F;
    int E, A, B;
    scanf("%lld %d %d %d", &F, &E, &A, &B);
    static pair<int,int> es[100];
    for (int i = 0; i < E; i++) {
      scanf("%d %d", &es[i].first, &es[i].second);
    }

    if (A == B) {
      puts("It is possible to move the furniture.");
      continue;
    }

    const int start = E, goal = E+1;
    DisjointSet s(E+2);
    for (int i = 0; i < E; i++) {
      if (A >= es[i].second && (A-es[i].second) % es[i].first == 0) {
        s.unite(start, i);
      }
      if (B >= es[i].second && (B-es[i].second) % es[i].first == 0) {
        s.unite(i, goal);
      }
    }
    for (int i = 0; i < E; i++) {
      for (int j = i+1; j < E; j++) {
        const long long f = solve(es[i].first, es[i].second, es[j].first, es[j].second);
        if (0 <= f && f <= F) {
          s.unite(i, j);
        }
      }
    }
    if (s.find(start, goal)) {
      puts("It is possible to move the furniture.");
    } else {
      puts("The furniture cannot be moved.");
    }
  }
  return 0;
}
