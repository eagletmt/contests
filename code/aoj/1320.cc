#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct kmp
{
  string pat;
  int len;
  vector<int> tbl;
  kmp(const string& s) : pat(s), len(s.size()), tbl(s.size())
  {
    tbl[0] = -1;
    tbl[1] = 0;
    for (int i = 2, j = 0; i < len;) {
      if (pat[i-1] == pat[j]) {
        tbl[i] = j+1;
        i++; j++;
      } else if (j > 0) {
        j = tbl[j];
      } else {
        tbl[i] = 0;
        i++;
      }
    }
  }

  pair<bool,int> search(const string& s) const
  {
    const int L = s.size();
    int i = 0;
    for (int m = 0; m+i < L;) {
      if (pat[i] == s[m+i]) {
        i++;
        if (i == len) {
          return make_pair(true, m);
        }
      } else {
        m = m + i - tbl[i];
        if (i > 0) {
          i = tbl[i];
        }
      }
    }
    return make_pair(false, i);
  }
};

int main()
{
  int N;
  while (cin >> N && N != 0) {
    vector<string> v;
    for (int i = 0; i < N; i++) {
      string s;
      cin >> s;
      v.push_back(s);
    }
    vector<kmp> cities;
    for (int i = 0; i < N; i++) {
      kmp k(v[i]);
      for (int j = 0; j < N; j++) {
        if (i != j && k.search(v[j]).first) {
          goto SKIP;
        }
      }
      cities.push_back(k);
SKIP:
      ;
    }
    N = cities.size();

    vector<vector<int> > memo(N, vector<int>(N));
    for (int i = 0; i < N; i++) {
      for (int j = 0; j < N; j++) {
        if (i == j) {
          continue;
        }
        const pair<bool,int> r = cities[j].search(cities[i].pat);
        memo[i][j] = cities[j].pat.size() - r.second;
      }
    }

    static const int INF = 10000000;
    vector<vector<int> > dp(1<<N, vector<int>(N, INF));
    for (int i = 0; i < N; i++) {
      dp[1<<i][i] = cities[i].pat.size();
    }
    for (unsigned s = 1; s < (1<<N); s++) {
      for (int i = 0; i < N; i++) {
        if (!(s & (1<<i))) {
          continue;
        }
        for (int j = 0; j < N; j++) {
          if (s & (1<<j)) {
            continue;
          }
          int& dp_next = dp[s|(1<<j)][j];
          dp_next = min(dp_next, dp[s][i] + memo[i][j]);
        }
      }
    }
    int ans = INF;
    for (int i = 0; i < N; i++) {
      ans = min(ans, dp[(1<<N)-1][i]);
    }
    cout << ans << endl;
  }
  return 0;
}
