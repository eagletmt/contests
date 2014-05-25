#include <cstdio>
#include <algorithm>
#include <functional>
using namespace std;

const int MAXN = 100000;
long long h[MAXN], w[MAXN];
long long ans[MAXN];
long long wsum[MAXN+1];
int pouring;

template <class Compare>/*{{{*/
struct SegmentTree
{
  const long long *cows;
  int *indexes;
  int N;
  Compare cmp;
  SegmentTree(const long long *cs, int n)
    : cows(cs), indexes(new int[4*n]), N(n)
  {
    fill_n(indexes, 4*N, -1);
    build(0, 0, N);
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
      if (cmp(cows[indexes[2*idx+1]], cows[indexes[2*idx+2]])) {
        indexes[idx] = indexes[2*idx+1];
      } else {
        indexes[idx] = indexes[2*idx+2];
      }
    }
  }

  inline long long query_value(int left, int right) const { return cows[query_index(left, right)]; }

  inline int query_index(int left, int right) const { return query_index(left, right, 0, 0, N); }

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
        if (cmp(cows[l], cows[r])) {
          return l;
        } else {
          return r;
        }
      }
    }
  }
};/*}}}*/

long long t = 0;
  template <class T>
void solve(int beg, int end, int prevh, const SegmentTree<T>& segtree)
{
  if (beg >= end) {
    return;
  }
  int lv = segtree.query_index(beg, end);
  if (lv < pouring) {
    solve(lv+1, end, h[lv], segtree);
    solve(beg, lv, h[lv], segtree);
  } else {
    solve(beg, lv, h[lv], segtree);
    solve(lv+1, end, h[lv], segtree);
  }
  ans[lv] = t + (wsum[end] - wsum[beg]);
  t += (prevh - h[lv]) * (wsum[end] - wsum[beg]);
}

int main()
{
  int N;
  scanf("%d", &N);
  long long m = 1LL<<50;
  for (int i = 0; i < N; i++) {
    scanf("%lld %lld", &w[i], &h[i]);
    wsum[i+1] = wsum[i] + w[i];
    if (h[i] < m) {
      m = h[i];
      pouring = i;
    }
  }
  SegmentTree<greater<long long> > segtree(h, N);
  int hh = segtree.query_value(0, N);
  solve(0, N, hh, segtree);
  for (int i = 0; i < N; i++) {
    printf("%lld\n", ans[i]);
  }
  return 0;
}
