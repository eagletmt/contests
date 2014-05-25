#include <cstdio>
using namespace std;

int main()
{
  int N;
  while (scanf("%d", &N) != EOF && N != 0) {
    static int a[1000][1000];
    for (int i = 0; i < N; i++) {
      for (int j = 0; j < N; j++) {
        scanf("%d", &a[i][j]);
      }
    }

    for (int i = 1; i < N; i++) {
      for (int j = 1; j < N; j++) {
        if (a[i-1][j-1] + a[i][j] != a[i-1][j] + a[i][j-1]) {
          puts("not homogeneous");
          goto NEXT;
        }
      }
    }
    puts("homogeneous");
NEXT:
    ;
  }
  return 0;
}
