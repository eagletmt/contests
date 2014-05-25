#include <cstdio>
#include <algorithm>
using namespace std;

char grid[1000][1001];
int R, C;

int solve()
{
  int r = 0;
  for (int i = 0; i < R; i++) {
    for (int j = 0; j < C; j++) {
      if (grid[i][j] == '#') {
        int k = i;
        while (k < R && grid[k][j] == '#') {
          ++k;
        }
        --k;
        int l = j;
        while (l < C && grid[i][l] == '#') {
          ++l;
        }
        --l;

        const int Y = min(l+1, C-1);
        for (int y = max(j-1, 0); y <= Y; y++) {
          if (i > 0 && grid[i-1][y] == '#') {
            return -1;
          }
          if (k < R-1 && grid[k+1][y] == '#') {
            return -1;
          }
        }
        const int X = min(k+1, R-1);
        for (int x = max(i-1, 0); x <= X; x++) {
          if (j > 0 && grid[x][j-1] == '#') {
            return -1;
          }
          if (l < C-1 && grid[x][l+1] == '#') {
            return -1;
          }
        }
        for (int x = i; x <= k; x++) {
          for (int y = j; y <= l; y++) {
            if (grid[x][y] != '#') {
              return -1;
            }
            grid[x][y] = '@';
          }
        }
        ++r;
      }
    }
  }
  return r;
}

int main()
{
  while (scanf("%d %d", &R, &C) != EOF && R != 0) {
    for (int i = 0; i < R; i++) {
      scanf("%s", grid[i]);
    }
    const int r = solve();
    if (r == -1) {
      puts("Bad placement.");
    } else {
      printf("There are %d ships.\n", r);
    }
  }
  return 0;
}
