#include <cstdio>
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
};

int main()
{
  int N;
  scanf("%d", &N);
  static bool dir[5000];
  for (int i = 0; i < N; i++) {
    char c[2];
    scanf("%1s", c);
    if (*c == 'F') {
      dir[i] = true;
    } else {
      dir[i] = false;
    }
  }

  static int d[5001];
  BinaryIndexedTree<int*> bit(d, N);
  int K = 0, M = 1000000;
  for (int k = 1; k <= N; k++) {
    fill_n(d, N+1, 0);
    int m = 0;
    for (int i = 0; i <= N-k; i++) {
      if ((dir[i] + bit.read(i+1)) % 2 == 0) {
        ++m;
        bit.add(i+1, 1);
        bit.add(k+i+1, -1);
      }
    }
    for (int i = N-k; i < N; i++) {
      if ((dir[i] + bit.read(i+1)) % 2 == 0) {
        goto FAIL;
      }
    }
    if (m < M) {
      K = k;
      M = m;
    }
FAIL:
    ;
  }
  printf("%d %d\n", K, M);
  return 0;
}
