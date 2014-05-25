#include <cstdio>
#include <algorithm>
using namespace std;

typedef enum { A, H } op_type;

struct automaton
{
  int state;
  automaton() : state(0) {}
  automaton& operator<<(op_type o)
  {
    static const int tbl[8][2] = {
      {1, 4},
      {2, 7},
      {3, 6},
      {0, 5},
      {5, 0},
      {6, 3},
      {7, 2},
      {4, 1},
    };
    state = tbl[state][o];
    return *this;
  }

  void operator()(char mat[310][310], int& M, int& N) const
  {
    int s = state;
    if (s & 4) {
      for (int i = 0; i < M/2; i++) {
        for (int j = 0; j < N; j++) {
          swap(mat[i][j], mat[M-i-1][j]);
        }
      }
      s &= 3;
    }
    while (s-- > 0) {
      static char t[310][310];
      for (int i = 0; i < M; i++) {
        for (int j = 0; j < N; j++) {
          t[j][M-i-1] = mat[i][j];
          mat[i][j] = '\0';
        }
      }
      swap(M, N);
      for (int i = 0; i < M; i++) {
        for (int j = 0; j < N; j++) {
          mat[i][j] = t[i][j];
          t[i][j] = '\0';
        }
      }
    }
  }
};

int main()
{
  int M, N;
  scanf("%d %d", &M, &N);
  static char mat[310][310];
  for (int i = 0; i < M; i++) {
    scanf("%s", mat[i]);
  }

  automaton a;
  int c;
  while ((c = getchar()) != EOF) {
    if (c == '\n') {
      continue;
    }
    switch (c) {
      case '1':
        a << H << A; break;
      case '2':
        a << H << A << A << A; break;
      case 'H':
        a << H; break;
      case 'V':
        a << H << A << A; break;
      case 'A':
      case 'Z':
        a << A; break;
      case 'B':
      case 'Y':
        a << A << A; break;
      case 'C':
      case 'X':
        a << A << A << A; break;
      default:
        throw "err";
    }
  }
  a(mat, M, N);
  printf("%d %d\n", M, N);
  for (int i = 0; i < M; i++) {
    puts(mat[i]);
  }
  return 0;
}
