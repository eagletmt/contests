#include <cstdio>
#include <algorithm>
using namespace std;

int main()
{
  int a[5];
  for (int i = 0; i < 5; i++) {
    scanf("%d", &a[i]);
  }

  static const int M = 100;
  static int x2[M*M], x3[M*M*M];
  int x2_size = 0, x3_size = 0;
  for (int i = -50; i <= 50; i++) {
    if (i == 0) {
      continue;
    }
    const int x = i*i*i;
    for (int j = -50; j <= 50; j++) {
      if (j == 0) {
        continue;
      }
      const int y = j*j*j;
      x2[x2_size++] = a[0]*x + a[1]*y;
      for (int k = -50; k <= 50; k++) {
        if (k == 0) {
          continue;
        }
        const int z = k*k*k;
        x3[x3_size++] = a[2]*x + a[3]*y + a[4]*z;
      }
    }
  }
  sort(x2, x2+x2_size);
  sort(x3, x3+x3_size);

  int c = 0;
  for (int i = 0; i < x2_size; i++) {
    const pair<int*, int*> p = equal_range(x3, x3+x3_size, x2[i]);
    c += distance(p.first, p.second);
  }
  printf("%d\n", c);
  return 0;
}
