#include <cstdio>
#include <algorithm>
using namespace std;

static const int N = 200;
int memo[N+1][N+1];

int grundyNumber(int w, int h)
{
  if (memo[w][h] != -1) {
    return memo[w][h];
  }
  bool s[N+1];
  fill_n(s, N+1, false);
  for (int k = 2; w-k >= 2; k++) {
    s[grundyNumber(w-k, h) ^ grundyNumber(k, h)] = true;
  }
  for (int k = 2; h-k >= 2; k++) {
    s[grundyNumber(w, h-k) ^ grundyNumber(w, k)] = true;
  }
  int n = 0;
  for (; s[n]; n++);
  return memo[w][h] = n;
}

int main()
{
  for (int i = 0; i <= N; i++) {
    fill_n(memo[i], N+1, -1);
  }
  memo[2][2] = 0;
  memo[3][2] = memo[2][3] = 0;
  int W, H;
  while (scanf("%d %d", &W, &H) != EOF) {
    puts(grundyNumber(W, H) == 0 ? "LOSE" : "WIN");
  }
  return 0;
}
