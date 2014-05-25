#include <iostream>
#include <vector>
#include <complex>
using namespace std;
typedef complex<int> P;

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

inline int cross(const P& a, const P& b) { return a.real()*b.imag() - b.real()*a.imag(); }

struct segment
{
  P a, b;
  segment() {}
  segment(const P& x, const P& y) : a(x), b(y) {}

  inline bool intersects(const segment& seg) const
  {
    return
      max(a.real(), b.real()) >= min(seg.a.real(), seg.b.real())
      && max(seg.a.real(), seg.b.real()) >= min(a.real(), b.real())
      && max(a.imag(), b.imag()) >= min(seg.a.imag(), seg.b.imag())
      && max(seg.a.imag(), seg.b.imag()) >= min(a.imag(), b.imag())
      && cross(seg.b - seg.a, a - seg.a) * cross(seg.b - seg.a, b - seg.a) <= 0
      && cross(b - a, seg.a - a) * cross(b - a, seg.b - a) <= 0;
  }
};

int main()
{
  int N;
  while (cin >> N && N != 0) {
    vector<segment> segs;
    for (int i = 0; i < N; i++) {
      int x1, y1, x2, y2;
      cin >> x1 >> y1 >> x2 >> y2;
      segs.push_back(segment(P(x1, y1), P(x2, y2)));
    }
    DisjointSet s(N);
    for (int i = 0; i < N; i++) {
      for (int j = 0; j < i; j++) {
        if (segs[i].intersects(segs[j])) {
          s.unite(i, j);
        }
      }
    }

    int a, b;
    while (cin >> a >> b && !(a == 0 && b == 0)) {
      --a;  --b;
      cout << (s.find(a, b) ? "" : "NOT ") << "CONNECTED" << endl;
    }
  }
  return 0;
}
