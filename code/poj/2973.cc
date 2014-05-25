#include <iostream>
#include <vector>
using namespace std;

bool match(const vector<int>& s, const vector<int>& c, int wild)
{
  for (int i = 0; i < 26; i++) {
    if (s[i] > 0) {
      if (s[i] > c[i]) {
        wild -= s[i] - c[i];
        if (wild < 0) {
          return false;
        }
      }
    }
  }
  return true;
}

int main()
{
  int N;
  while (cin >> N && N != 0) {
    vector<vector<int> > dict;
    for (int i = 0; i < N; i++) {
      string word;
      cin >> word;
      vector<int> c(26, 0);
      for (string::const_iterator it(word.begin()); it != word.end(); ++it) {
        ++c[*it - 'A'];
      }
      dict.push_back(c);
    }
    string tile;
    cin >> tile;
    int wild = 0;
    vector<int> c(26, 0);
    for (string::const_iterator it(tile.begin()); it != tile.end(); ++it) {
      if (*it == '_') {
        ++wild;
      } else {
        ++c[*it-'A'];
      }
    }
    int ans = 0;
    for (vector<vector<int> >::const_iterator it(dict.begin()); it != dict.end(); ++it) {
      if (match(*it, c, wild)) {
        ++ans;
      }
    }
    cout << ans << endl;
  }
  return 0;
}
