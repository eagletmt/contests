#include <iostream>
#include <sstream>
#include <vector>
#include <set>
#include <cctype>
#include <iterator>
#include <algorithm>
using namespace std;

char downcase(char c) { return tolower(c); }
char cleanup(char c) { return isalpha(c) ? tolower(c) : ' '; }

int main()
{
  ios::sync_with_stdio(false);
  for (int K, E, Ti = 1; cin >> K >> E; Ti++) {
    set<string> keywords;
    for (int i = 0; i < K; i++) {
      string s;
      cin >> s;
      transform(s.begin(), s.end(), s.begin(), downcase);
      keywords.insert(s);
    }

    cin.ignore();
    vector<string> ans;
    int m = 0;
    for (int i = 0; i < E; i++) {
      string line;
      getline(cin, line);
      const string orig_line = line;
      transform(line.begin(), line.end(), line.begin(), cleanup);
      istringstream iss(line);
      int c = 0;
      for (string s; iss >> s;) {
        if (keywords.count(s)) {
          ++c;
        }
      }
      if (c > m) {
        m = c;
        ans.clear();
        ans.push_back(orig_line);
      } else if (c == m) {
        ans.push_back(orig_line);
      }
    }
    cout << "Excuse Set #" << Ti << endl;
    copy(ans.begin(), ans.end(), ostream_iterator<string>(cout, "\n"));
    cout << endl;
  }
  return 0;
}
