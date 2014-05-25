#include <iostream>
#include <sstream>
#include <cctype>
#include <algorithm>
using namespace std;

int main()
{
  string s;
  getline(cin, s);
  bool seen[26];
  fill_n(seen, 26, false);
  stringstream ss;
  for (string::const_iterator it = s.begin(); it != s.end(); ++it) {
    switch (*it) {
      case 'A':
      case 'E':
      case 'I':
      case 'O':
      case 'U':
        break;
      default:
        if (isupper(*it)) {
          if (!seen[*it-'A']) {
            seen[*it-'A'] = true;
            ss << *it;
          }
        } else {
          ss << *it;
        }
    }
  }

  ostringstream oss;
  ss >> s;
  oss << s;
  while (ss >> s) {
    if (isupper(s[0])) {
      oss << ' ';
    }
    oss << s;
  }
  cout << oss.str() << endl;
  return 0;
}
