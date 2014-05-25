#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include <cctype>
using namespace std;

struct calc
{
  map<char,int> env;
  vector<char> preinc, predec, postinc, postdec;
  void pre(string& s)
  {
    for (string::iterator it = s.begin(); it != s.end() && it+1 != s.end() && it+2 != s.end(); ++it) {
      if (*it == '+' && *(it+1) == '+' && isalpha(*(it+2))) {
        preinc.push_back(*(it+2));
        it = s.erase(it);
        it = s.erase(it);
      } else if (*it == '-' && *(it+1) == '-' && isalpha(*(it+2))) {
        predec.push_back(*(it+2));
        it = s.erase(it);
        it = s.erase(it);
      }
    }
    for (string::iterator it = s.begin(); it != s.end() && it+1 != s.end() && it+2 != s.end();) {
      if (isalpha(*it) && *(it+1) == '+' && *(it+2) == '+') {
        postinc.push_back(*it);
        ++it;
        it = s.erase(it);
        it = s.erase(it);
      } else if (isalpha(*it) && *(it+1) == '-' && *(it+2) == '-') {
        postdec.push_back(*it);
        ++it;
        it = s.erase(it);
        it = s.erase(it);
      } else {
        ++it;
      }
    }
  }

  int f(const string& s)
  {
    for (vector<char>::const_iterator it = preinc.begin(); it != preinc.end(); ++it) {
      get(*it);
      ++env[*it];
    }
    for (vector<char>::const_iterator it = predec.begin(); it != predec.end(); ++it) {
      get(*it);
      --env[*it];
    }
    int n = 0;
    char o = '+';
    for (string::const_iterator it = s.begin(); it != s.end(); ++it) {
      if (isalpha(*it)) {
        if (o == '+') {
          n += get(*it);
        } else if (o == '-') {
          n -= get(*it);
        } else {
          throw "err";
        }
      } else {
        o = *it;
      }
    }
    for (vector<char>::const_iterator it = postinc.begin(); it != postinc.end(); ++it) {
      ++env[*it];
    }
    for (vector<char>::const_iterator it = postdec.begin(); it != postdec.end(); ++it) {
      --env[*it];
    }
    return n;
  }

  bool has(char c) const { return env.count(c); }
  int get(char c)
  {
    if (!has(c)) {
      env[c] = c-'a'+1;
    }
    return env[c];
  }
};

int main()
{
  for (string line; getline(cin, line);) {
    cout << "Expression: " << line << endl;
    line.erase(remove(line.begin(), line.end(), ' '), line.end());
    calc c;
    c.pre(line);
    int ans = c.f(line);
    cout << "    value = " << ans << endl;
    for (char i = 'a'; i <= 'z'; i++) {
      if (c.has(i)) {
        cout << "    " << i << " = " << c.get(i) << endl;
      }
    }
  }
  return 0;
}
