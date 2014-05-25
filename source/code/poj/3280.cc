#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main()
{
  int N, M;
  cin >> N >> M;
  string s;
  cin >> s;
  int cost[26];
  for (int i = 0; i < N; i++) {
    string c;
    int a, r;
    cin >> c >> a >> r;
    cost[c[0]-'a'] = min(a, r);
  }

  static int dp[2000][2001];
  static const int INF = 10000000;
  for (int i = 0; i < M; i++) {
    fill_n(dp[i], M+1, INF);
    dp[i][i] = dp[i][i+1] = 0;
  }
  for (int len = 0; len < M; len++) {
    for (int i = 0; i < M; i++) {
      const int j = i+len;
      if (i > 0) {
        dp[i-1][j] = min(dp[i-1][j], dp[i][j] + cost[s[i-1]-'a']);
      }
      if (j < M) {
        dp[i][j+1] = min(dp[i][j+1], dp[i][j] + cost[s[j]-'a']);
      }
      if (i > 0 && j < M && s[i-1] == s[j]) {
        dp[i-1][j+1] = min(dp[i-1][j+1], dp[i][j]);
      }
    }
  }
  cout << dp[0][M] << endl;
  return 0;
}
