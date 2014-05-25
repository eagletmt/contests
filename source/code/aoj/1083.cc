#include <cstdio>
#include <map>
#include <algorithm>
using namespace std;

struct Incubator
{
  static const int H = 20;
  static const int BASE = (1<<(H-1));
  int tree[1<<H];
  int limit;
  map<int,int> m;
  int rev[400000];

  void init(int l)
  {
    fill_n(tree, 1<<H, 0);
    fill_n(rev, 400000, -1);
    limit = l;
    m.clear();
  }

  void add(int idx, int v)
  {
    while (idx != 0) {
      tree[idx-1] += v;
      idx >>= 1;
    }
  }

  void incubate(int x)
  {
    if (tree[0] == limit) {
      enkan_idx(0);
    }
    const int i = m.size();
    m[x] = i;
    rev[i] = x;
    add(i + BASE, 1);
  }

  void enkan(int x)
  {
    add(m[x] + BASE, -1);
  }

  void enkan_idx(int n)
  {
    add(find(n), -1);
  }

  int query(int n) const
  {
    return rev[find(n) - BASE];
  }

  int find(int n) const
  {
    int idx = 1;
    while (idx < BASE) {
      const int l = idx<<1;
      const int r = l+1;
      if (n < tree[l-1]) {
        idx = l;
      } else {
        idx = r;
        n -= tree[l-1];
      }
    }
    return idx;
  }
};

int main()
{
  static Incubator qb;
  int Q, L;
  while (scanf("%d %d", &Q, &L) != EOF && Q != 0) {
    qb.init(L);
    for (int i = 0; i < Q; i++) {
      int q, x;
      scanf("%d %d", &q, &x);
      switch (q) {
        case 0:
          qb.incubate(x);
          break;
        case 1:
          qb.enkan_idx(x-1);
          break;
        case 2:
          printf("%d\n", qb.query(x-1));
          break;
        case 3:
          qb.enkan(x);
          break;
      }
    }
    puts("end");
  }
  return 0;
}
