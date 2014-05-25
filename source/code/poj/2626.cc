#include <iostream>
#include <vector>
using namespace std;

int main()
{
  vector<pair<int,int> > v;
  int w, b;
  while (cin >> w >> b) {
    v.push_back(make_pair(w, b));
  }

  const int N = v.size();
  vector<vector<vector<int> > > dp(N+1, vector<vector<int> >(16, vector<int>(16, 0)));
  for (int i = 0; i < N; i++) {
    for (int j = 0; j <= 15; j++) {
      for (int k = 0; k <= 15; k++) {
        // skip i
        dp[i+1][j][k] = max(dp[i+1][j][k], dp[i][j][k]);
        // choose i as white
        if (j+1 <= 15) {
          dp[i+1][j+1][k] = max(dp[i+1][j+1][k], dp[i][j][k] + v[i].first);
        }
        // choose i as black
        if (k+1 <= 15) {
          dp[i+1][j][k+1] = max(dp[i+1][j][k+1], dp[i][j][k] + v[i].second);
        }
      }
    }
  }
  cout << dp[N][15][15] << endl;
  return 0;
}
