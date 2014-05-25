#include <cstdio>
#include <algorithm>
using namespace std;

int main()
{
  int T;
  scanf("%d", &T);
  while (T-- > 0) {
    int N, S;
    scanf("%d %d", &N, &S);
    static int a[100000];
    for (int i = 0; i < N; i++) {
      scanf("%d", &a[i]);
    }

    int ans = N;
    int s = 0;
    int j = 0;
    for (int i = 0; i < N; i++) {
      s += a[i];
      while (j <= i && s >= S) {
        ans = min(ans, i-j+1);
        s -= a[j];
        j++;
      }
    }
    printf("%d\n", ans == N ? 0 : ans);
  }
  return 0;
}
