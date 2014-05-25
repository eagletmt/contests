#include <iostream>
#include <vector>
#include <map>
using namespace std;

void dfs(const vector<vector<int> >& g, int n, vector<vector<int> >& dp, vector<vector<bool> >& uniq)
{
  dp[n][0] = 0; dp[n][1] = 1;
  uniq[n][0] = uniq[n][1] = true;
  for (vector<int>::const_iterator it = g[n].begin(); it != g[n].end(); ++it) {
    dfs(g, *it, dp, uniq);
    if (dp[*it][0] == dp[*it][1]) {
      dp[n][0] += dp[*it][0];
      uniq[n][0] = false;
    } else if (dp[*it][0] < dp[*it][1]) {
      dp[n][0] += dp[*it][1];
      uniq[n][0] = uniq[n][0] && uniq[*it][1];
    } else {
      dp[n][0] += dp[*it][0];
      uniq[n][0] = uniq[n][0] && uniq[*it][0];
    }
    dp[n][1] += dp[*it][0];
    uniq[n][1] = uniq[n][1] && uniq[*it][0];
  }
}

int main()
{
  int N;
  while (cin >> N && N != 0) {
    map<string,int> m;
    string s1;
    cin >> s1;
    m.insert(make_pair(s1, 0));
    vector<vector<int> > g(N);
    for (int i = 0; i < N-1; i++) {
      string s2;
      cin >> s1 >> s2;
      if (!m.count(s1)) {
        m.insert(make_pair(s1, m.size()));
      }
      if (!m.count(s2)) {
        m.insert(make_pair(s2, m.size()));
      }
      g[m[s2]].push_back(m[s1]);
    }

    vector<vector<int> > dp(N, vector<int>(2));
    vector<vector<bool> > uniq(N, vector<bool>(2));
    dfs(g, 0, dp, uniq);
    int ans;
    bool u;
    if (dp[0][0] == dp[0][1]) {
      ans = dp[0][0];
      u = false;
    } else if (dp[0][0] < dp[0][1]) {
      ans = dp[0][1];
      u = uniq[0][1];
    } else {
      ans = dp[0][0];
      u = uniq[0][0];
    }
    cout << ans << ' ' << (u ? "Yes" : "No") << endl;
  }
  return 0;
}
