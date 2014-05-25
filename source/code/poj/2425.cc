#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;

int memo[1000];
int grundyNumber(const vector<vector<int> >& g, int x)
{
  int& n = memo[x];
  if (n != -1) {
    return n;
  }
  bool s[1000];
  fill_n(s, 1000, false);
  for (vector<int>::const_iterator it = g[x].begin(); it != g[x].end(); ++it) {
    s[grundyNumber(g, *it)] = true;
  }
  for (n = 0; s[n]; ++n);
  return n;
}

int main()
{
  int N;
  while (scanf("%d", &N) != EOF && N != 0) {
    vector<vector<int> > g(N);
    for (int i = 0; i < N; i++) {
      int X;
      scanf("%d", &X);
      for (int j = 0; j < X; j++) {
        int v;
        scanf("%d", &v);
        g[i].push_back(v);
      }
    }

    fill_n(memo, 1000, -1);
    int M;
    while (scanf("%d", &M) != EOF && M != 0) {
      int s = 0;
      while (M-- > 0) {
        int x;
        scanf("%d", &x);
        s ^= grundyNumber(g, x);
      }
      puts(s == 0 ? "LOSE" : "WIN");
    }
  }
  return 0;
}
