#include <cstdio>
#include <vector>
#include <functional>
#include <algorithm>
using namespace std;

template <class T, class Compare>
struct SegmentTree/*{{{*/
{
  vector<T>& mem;
  vector<int> indexes;
  Compare cmp;
  SegmentTree(vector<T>& cs)
    : mem(cs), indexes(4*cs.size(), -1)
  {
    build(0, 0, cs.size());
  }

  void build(int idx, int left, int right)
  {
    if (left+1 == right) {
      indexes[idx] = left;
    } else {
      const int mid = (left + right)/2;
      build(2*idx+1, left, mid);
      build(2*idx+2, mid, right);
      // minimum in [left, right)
      if (cmp(mem[indexes[2*idx+1]], mem[indexes[2*idx+2]])) {
        indexes[idx] = indexes[2*idx+1];
      } else {
        indexes[idx] = indexes[2*idx+2];
      }
    }
  }

  inline int query_index(int left, int right) const { return query_index(left, right, 0, 0, mem.size()); }

  int query_index(int left, int right, int i, int a, int b) const
  {
    // [a, b) is the range of indexes[i]
    if (b <= left || right <= a) {
      // does not intersect
      return -1;
    } else if (left <= a && b <= right) {
      // contains
      return indexes[i];
    } else {
      const int m = (a+b)/2;
      const int l = query_index(left, right, 2*i+1, a, m);
      const int r = query_index(left, right, 2*i+2, m, b);
      if (l == -1) {
        return r;
      } else if (r == -1) {
        return l;
      } else {
        if (cmp(mem[l], mem[r])) {
          return l;
        } else {
          return r;
        }
      }
    }
  }

};/*}}}*/

static const int MAXN = 50000;
int ansl[MAXN], ansr[MAXN];

  template <class T, class Compare>
void solve(const SegmentTree<T, Compare>& seg, int self, int left, int right)
{
  if (left == right) {
    return;
  }
  if (left == self) {
    ansl[self] = 0;
  } else {
    const int l = seg.query_index(left, self);
    ansl[self] = l+1;
    solve(seg, l, left, self);
  }
  if (right == self+1) {
    ansr[self] = 0;
  } else {
    const int r = seg.query_index(self+1, right);
    ansr[self] = r+1;
    solve(seg, r, self+1, right);
  }
}

int main()
{
  int T;
  scanf("%d", &T);
  for (int Ti = 1; Ti <= T; Ti++) {
    int N;
    scanf("%d", &N);
    vector<int> v(N);
    int tallest = 0, height = 0;
    for (int i = 0; i < N; i++) {
      scanf("%d", &v[i]);
      if (v[i] > height) {
        height = v[i];
        tallest = i;
      }
    }

    const SegmentTree<int, greater<int> > seg(v);
    printf("Case %d:\n", Ti);
    solve(seg, tallest, 0, N);
    for (int i = 0; i < N; i++) {
      printf("%d %d\n", ansl[i], ansr[i]);
    }
  }
  return 0;
}
