#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;

int N, M;
vector<vector<pair<int,int> > > g;
int dp[3000][3000];
int price[3000];

int dfs(int n)
{
  if (n < N-M) {
    // transmitter
    dp[n][0] = 0;
    int cnt = 0;
    for (vector<pair<int,int> >::const_iterator it = g[n].begin(); it != g[n].end(); ++it) {
      const int a = it->first;
      const int c = it->second;
      const int r = dfs(a);
      static int tmp[3000];
      copy(dp[n], dp[n]+cnt+1, tmp);
      for (int i = 0; i <= cnt; i++) {
        for (int j = r; j > 0; j--) {
          dp[n][i+j] = max(dp[n][i+j], tmp[i] + dp[a][j] - c);
        }
      }
      cnt += r;
    }
    return cnt;
  } else {
    // user
    dp[n][0] = 0;
    dp[n][1] = price[n];
    return 1;
  }
}

int main()
{
  scanf("%d %d", &N, &M);
  g.resize(N);
  for (int i = 0; i < N-M; i++) {
    int K;
    scanf("%d", &K);
    for (int j = 0; j < K; j++) {
      int A, C;
      scanf("%d %d", &A, &C);
      --A;
      g[i].push_back(make_pair(A, C));
    }
  }
  for (int i = 0; i < M; i++) {
    scanf("%d", &price[N-M+i]);
  }

  for (int i = 0; i < N; i++) {
    for (int j = 0; j <= M; j++) {
      dp[i][j] = -10000000;
    }
  }
  dfs(0);
  for (int i = M; i >= 0; i--) {
    if (dp[0][i] >= 0) {
      printf("%d\n", i);
      break;
    }
  }
  return 0;
}
