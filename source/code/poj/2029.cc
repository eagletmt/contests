#include <cstdio>
#include <vector>
using namespace std;

int main()
{
  int N;
  while (scanf("%d", &N) != EOF && N != 0) {
    int W, H;
    scanf("%d %d", &W, &H);
    vector<vector<int> > v(H+1, vector<int>(W+1, 0));
    for (int i = 0; i < N; i++) {
      int x, y;
      scanf("%d %d", &x, &y);
      ++v[y][x];
    }
    int S, T;
    scanf("%d %d", &S, &T);
    for (int i = 1; i <= H; i++) {
      for (int j = 1; j <= W; j++) {
        v[i][j] += v[i-1][j] + v[i][j-1] - v[i-1][j-1];
      }
    }

    int ans = 0;
    for (int i = T; i <= H; i++) {
      for (int j = S; j <= W; j++) {
        ans = max(ans, v[i][j] - v[i-T][j] - v[i][j-S] + v[i-T][j-S]);
      }
    }
    printf("%d\n", ans);
  }
  return 0;
}
