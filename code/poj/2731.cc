#include <iostream>
#include <sstream>
#include <vector>
#include <set>
#include <cctype>
#include <algorithm>
using namespace std;

long long solve(const string& abbr, const vector<string>& words)
{
  static long long dp[200][200];
  const int N = words.size(), M = abbr.size();
  for (int i = 0; i < N; i++) {
    fill_n(dp[i], M, 0);
  }
  for (string::const_iterator it = words[0].begin(); it != words[0].end(); ++it) {
    for (int j = M-1; j >= 0; j--) {
      if (*it == abbr[j]) {
        if (j == 0) {
          ++dp[0][j];
        } else {
          dp[0][j] += dp[0][j-1];
        }
      }
    }
  }
  for (int i = 1; i < N; i++) {
    const string& s = words[i];
    for (string::const_iterator it = s.begin(); it != s.end(); ++it) {
      for (int j = M-1; j >= i; j--) {
        if (*it == abbr[j]) {
          dp[i][j] += dp[i-1][j-1] + dp[i][j-1];
        }
      }
    }
  }
  return dp[N-1][M-1];
}

int main()
{
  ios::sync_with_stdio(false);
  int N;
  while (cin >> N && N != 0) {
    set<string> ignore;
    for (int i = 0; i < N; i++) {
      string s;
      cin >> s;
      ignore.insert(s);
    }
    cin.ignore();
    for (string s; getline(cin, s) && s != "LAST CASE";) {
      istringstream iss(s);
      string t;
      iss >> t;
      vector<string> words;
      while (iss >> s) {
        if (!ignore.count(s)) {
          words.push_back(s);
        }
      }
      cout << t << " ";
      for (string::iterator it = t.begin(); it != t.end(); ++it) {
        *it = tolower(*it);
      }
      long long ans = solve(t, words);
      if (ans == 0) {
        cout << "is not a valid abbreviation" << endl;
      } else {
        cout << "can be formed in " << ans << " ways" << endl;
      }
    }
  }
  return 0;
}
