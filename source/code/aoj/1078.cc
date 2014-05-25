#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

vector<string> split(const string& s, char d)
{
  vector<string> r;
  for (string::const_iterator it = s.begin();;) {
    string::const_iterator jt = find(it, s.end(), d);
    if (jt == s.end()) {
      r.push_back(string(it, s.end()));
      return r;
    } else {
      r.push_back(string(it, jt));
      it = jt+1;
    }
  }
}
int main()
{
  string line;
  while (cin >> line && line != "#") {
    vector<string> clauses = split(line, '|');
    for (vector<string>::const_iterator it = clauses.begin(); it != clauses.end(); ++it) {
      vector<string> lits = split(it->substr(1, it->size()-2), '&');
      vector<int> v(100, 0);
      for (vector<string>::const_iterator jt = lits.begin(); jt != lits.end(); ++jt) {
        if ((*jt)[0] == '~') {
          v[(*jt)[1]-'A'] |= 1<<1;
        } else {
          v[(*jt)[0]-'A'] |= 1<<0;
        }
      }
      if (find(v.begin(), v.end(), 3) == v.end()) {
        cout << "yes" << endl;
        goto NEXT;
      }
    }
    cout << "no" << endl;
NEXT:
    ;
  }
  return 0;
}
