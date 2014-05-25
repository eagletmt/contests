#include <cstdio>
#include <algorithm>
using namespace std;
static const int MAXX = 1<<10, MAXY = 1<<10;

template <class T>
struct BinaryIndexedTree2
{
  T tree[MAXX+1][MAXY+1];
  int X, Y;

  T read(int x, int y) const
  {
    T sum = 0;
    while (x > 0) {
      sum += read_(x, y);
      x -= x & -x;
    }
    return sum;
  }

  T read_(int x, int y) const
  {
    T sum = 0;
    while (y > 0) {
      sum += tree[x][y];
      y -= y & -y;
    }
    return sum;
  }

  void add(int x, int y, const T& v)
  {
    while (x <= X) {
      add_(x, y, v);
      x += x & -x;
    }
  }

  void add_(int x, int y, const T& v)
  {
    while (y <= Y) {
      tree[x][y] += v;
      y += y & -y;
    }
  }
};

int main()
{
  int insn;
  static BinaryIndexedTree2<int> bit;
  int S;
  while (scanf("%d", &insn) != EOF && insn != 3) {
    switch (insn) {
      case 0:
        {
          scanf("%d", &S);
          bit.X = bit.Y = S;
          for (int i = 0; i <= S; i++) {
            fill_n(bit.tree[i], S+1, 0);
          }
        }
        break;
      case 1:
        {
          int X, Y, A;
          scanf("%d %d %d", &X, &Y, &A);
          bit.add(X+1, Y+1, A);
        }
        break;
      case 2:
        {
          int L, B, R, T;
          scanf("%d %d %d %d", &L, &B, &R, &T);
          printf("%d\n", bit.read(R+1, T+1) - bit.read(L, T+1) - bit.read(R+1, B) + bit.read(L, B));
        }
        break;
    }
  }
  return 0;
}
