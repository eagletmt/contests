#include <cstdio>
using namespace std;

int main()
{
  int N;
  scanf("%d", &N);
  static bool a[10000][1000];
  for (int i = 0; i < N; i++) {
    int C;
    scanf("%d", &C);
    for (int j = 0; j < C; j++) {
      int x;
      scanf("%d", &x);
      --x;
      a[x][i] = true;
    }
  }

  int Q;
  scanf("%d", &Q);
  while (Q-- > 0) {
    int x, y;
    scanf("%d %d", &x, &y);
    --x;  --y;
    bool ok = false;
    for (int i = 0; i < N; i++) {
      if (a[x][i] && a[y][i]) {
        ok = true;
        break;
      }
    }
    puts(ok ? "Yes" : "No");
  }
  return 0;
}
