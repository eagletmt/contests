#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;

template <class T>
struct BinaryIndexedTree
{
  T tree;
  const int size;
  BinaryIndexedTree(const T& t, int s) : tree(t), size(s) {}
  int read(int i) const
  {
    int sum = 0;
    while (i > 0) {
      sum += tree[i];
      i -= i & -i;
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
};

int main()
{
  int T;
  scanf("%d", &T);
  for (int Ti = 1; Ti <= T; Ti++) {
    int N, M, K;
    scanf("%d %d %d", &N, &M, &K);
    vector<pair<int,int> > v(K);
    for (int i = 0; i < K; i++) {
      scanf("%d %d", &v[i].first, &v[i].second);
    }

    sort(v.begin(), v.end());
    static int mem[1001];
    fill_n(mem, M+1, 0);
    BinaryIndexedTree<int*> bit(mem, M);
    long long ans = 0LL;
    for (vector<pair<int,int> >::const_iterator it(v.begin()); it != v.end(); ++it) {
      ans += static_cast<long long>(bit.read(M - it->second + 1));
      bit.add(M - it->second + 2, 1);
    }
    printf("Test case %d: %lld\n", Ti, ans);
  }
  return 0;
}
