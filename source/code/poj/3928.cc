#include <cstdio>
#include <algorithm>
using namespace std;

template <class T>/*{{{*/
struct BinaryIndexedTree
{
  T tree;
  const int size;
  BinaryIndexedTree(const T& t, int s) : tree(t), size(s) {}
  // i 番目までの要素の累積和
  int read(int i) const
  {
    int sum = 0;
    while (i > 0) {
      sum += tree[i];
      i -= i & -i;
    }
    return sum;
  }

  // i 番目の要素
  int read_single(int i) const
  {
    int sum = tree[i];
    if (i > 0) {
      const int z = i - (i & -i);
      --i;
      while (i != z) {
        sum -= tree[i];
        i -= (i & -i);
      }
    }
    return sum;
  }

  void add(int i, int v)
  {
    while (i <= size) {
      tree[i] += v;
      i += (i & -i);
    }
  }
};/*}}}*/

int main()
{
  int T;
  scanf("%d", &T);
  while (T-- > 0) {
    int N;
    scanf("%d", &N);
    static int a[20000];
    for (int i = 0; i < N; i++) {
      scanf("%d", &a[i]);
    }
    static const int M = 100000;
    static int mem[M+1];
    fill_n(mem, M+1, 0);
    BinaryIndexedTree<int*> bit(mem, M);
    static int xs[20000];
    for (int i = 0; i < N; i++) {
      xs[i] = bit.read(a[i]);
      bit.add(a[i], 1);
    }
    fill_n(mem, M+1, 0);
    long long ans = 0;
    for (int i = N-1; i >= 0; i--) {
      int n = bit.read(a[i]);
      ans += static_cast<long long>(xs[i] * ((N-i-1)-n));
      ans += static_cast<long long>((i-xs[i]) * n);
      bit.add(a[i], 1);
    }
    printf("%lld\n", ans);
  }
  return 0;
}
