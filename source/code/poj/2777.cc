#include <cstdio>
#include <algorithm>
using namespace std;

static const int MAXL = 100000;

struct SegmentTree
{
  unsigned tree[4*MAXL];
  int L;
  SegmentTree(int l) : L(l)
  {
    fill_n(tree, 4*MAXL, 0);
    tree[0] = 1<<0;
  }

  void paint(int from, int to, int c)
  {
    paint(from, to, c, 0, 0, L);
  }
  void paint(int from, int to, int c, int i, int left, int right)
  {
    if (right <= from || to <= left) {
      // does not intersect
    } else if (from <= left && right <= to) {
      // included
      tree[i] = 1<<c;
    } else {
      if (__builtin_popcount(tree[i]) == 1) {
        tree[2*i+1] = tree[2*i+2] = tree[i];
      }
      const int m = (left+right)/2;
      paint(from, to, c, 2*i+1, left, m);
      paint(from, to, c, 2*i+2, m, right);
      tree[i] = tree[2*i+1] | tree[2*i+2];
    }
  }

  int query(int from, int to) const
  {
    return __builtin_popcount(query(from, to, 0, 0, L));
  }
  unsigned query(int from, int to, int i, int left, int right) const
  {
    if (right <= from || to <= left) {
      // does not intersect
      return 0;
    } else if (from <= left && right <= to) {
      // included
      return tree[i];
    } else {
      if (__builtin_popcount(tree[i]) == 1) {
        return tree[i];
      } else {
        const int m = (left+right)/2;
        return query(from, to, 2*i+1, left, m) | query(from, to, 2*i+2, m, right);
      }
    }
  }
};

int main()
{
  int L, T, O;
  scanf("%d %d %d", &L, &T, &O);
  static SegmentTree segtree(L);
  while (O-- > 0) {
    char o[4];
    int A, B;
    scanf("%s %d %d", o, &A, &B);
    if (A > B) {
      swap(A, B);
    }
    --A;
    if (*o == 'C') {
      int C;
      scanf("%d", &C);
      --C;
      segtree.paint(A, B, C);
    } else {
      printf("%d\n", segtree.query(A, B));
    }
  }
  return 0;
}
