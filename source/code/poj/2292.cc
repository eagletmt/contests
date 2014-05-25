#include <iostream>
#include <vector>
using namespace std;

int main()
{
  static int c2i[128];
  static char i2c[30];
  for (int i = 0; i < 26; i++) {
    c2i['a'+i] = i;
    i2c[i] = 'a'+i;
  }
  c2i['+'] = 26;
  i2c[26] = '+';
  c2i['*'] = 27;
  i2c[27] = '*';
  c2i['/'] = 28;
  i2c[28] = '/';
  c2i['?'] = 29;
  i2c[29] = '?';

  ios::sync_with_stdio(false);
  int T;
  cin >> T;
  while (T-- > 0) {
    int M;
    cin >> M;
    vector<int> cnt(30, 0);
    for (int i = 0; i < M; i++) {
      string s;
      cin >> s;
      for (string::const_iterator it = s.begin(); it != s.end(); ++it) {
        ++cnt[c2i[int(*it)]];
      }
    }

    static const int INF = 10000000;
    vector<vector<int> > dp(30, vector<int>(12, INF));
    vector<vector<int> > dp_prev(30, vector<int>(12, -1));
    dp[0][0] = 0;

    for (int k = 1; k < 12; k++) {
      for (int i = 0; i < 30; i++) {
        for (int j = 0; j < i; j++) {
          int s = 0;
          for (int x = j; x < i; x++) {
            s += cnt[x]*(x-j);
          }
          if (dp[j][k-1]+s < dp[i][k]) {
            dp[i][k] = dp[j][k-1]+s;
            dp_prev[i][k] = j;
          }
        }
      }
    }
    int mincost = INF;
    int idx = -1;
    for (int i = 0; i < 30; i++) {
      int s = 0;
      for (int j = i; j < 30; j++) {
        s += cnt[j] * (j-i);
      }
      if (dp[i][11]+s < mincost) {
        mincost = dp[i][11]+s;
        idx = i;
      }
    }
    char ans[12];
    ans[11] = '\0';
    for (int k = 11; k > 0; k--) {
      ans[k-1] = i2c[idx];
      idx = dp_prev[idx][k];
    }
    cout << ans << endl;
  }
  return 0;
}
