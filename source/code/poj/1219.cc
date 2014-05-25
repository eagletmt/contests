#include <iostream>
#include <vector>
#include <cctype>
using namespace std;

bool valid(const string& s)
{
  if (s.size() != 5) {
    return false;
  }
  for (string::const_iterator it = s.begin(); it != s.end(); ++it) {
    if (!isupper(*it)) {
      return false;
    }
  }
  return true;
}

void solve(const vector<string>& lines)
{
  const string& ans = lines[0];
  string prev = ".....";
  prev[0] = ans[0];
  cout << prev << endl;
  vector<int> cnt(128, 0);
  for (string::const_iterator it = ans.begin(); it != ans.end(); ++it) {
    ++cnt[*it];
  }

  const int N = min(lines.size(), 6U);
  for (int i = 1; i < N; i++) {
    vector<int> c(cnt);
    if (!valid(lines[i])) {
      cout << prev << endl;
    } else {
      prev = "@@@@@";
      for (int j = 0; j < 5; j++) {
        const char x = lines[i][j];
        if (c[x] == 0) {
          prev[j] = '.';
        } else if (ans[j] == x) {
          --c[x];
          prev[j] = x;
        }
      }
      for (int j = 0; j < 5; j++) {
        const char x = lines[i][j];
        if (prev[j] == '@') {
          if (c[x] != 0) {
            prev[j] = tolower(x);
            --c[x];
          } else {
            prev[j] = '.';
          }
        }
      }
      cout << prev << endl;
      if (lines[i] == prev) {
        return;
      }
    }
  }

  for (string::const_iterator it = ans.begin(); it != ans.end(); ++it) {
    cout << char(tolower(*it));
  }
  cout << endl;
}

int main()
{
  string s;
  vector<string> lines;
  while (getline(cin, s) && s != "LINGO") {
    if (s.empty()) {
      if (!lines.empty()) {
        cout << endl;
        solve(lines);
        lines.clear();
      }
    } else {
      lines.push_back(s);
    }
  }
  return 0;
}
