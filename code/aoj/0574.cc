#include <cstdio>
#include <algorithm>
using namespace std;

int main()
{
  int N, M;
  scanf("%d %d", &N, &M);
  static int a[5001][5001];
  for (int i = 0; i < M; i++) {
    int A, B, X;
    scanf("%d %d %d", &A, &B, &X);
    a[A][B] = X+1;
  }

  int ans = 0;
  for (int i = 1; i <= N; i++) {
    for (int j = 1; j <= i; j++) {
      a[i][j] = max(a[i][j], a[i-1][j] - 1);
      a[i][j] = max(a[i][j], a[i-1][j-1] - 1);
      if (a[i][j] > 0) {
        ++ans;
      }
    }
  }
  printf("%d\n", ans);
  return 0;
}
