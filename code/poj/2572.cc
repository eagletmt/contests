#include <iostream>
#include <sstream>
#include <algorithm>
using namespace std;

int f(const string& s)
{
  int n = 0;
  for (string::const_reverse_iterator it = s.rbegin(); it != s.rend(); ++it) {
    n = 10*n + (*it - '0');
  }
  return n;
}

int main()
{
  for (string s; getline(cin, s);) {
    replace(s.begin(), s.end(), '+', ' ');
    replace(s.begin(), s.end(), '=', ' ');
    istringstream iss(s);
    string a, b, c;
    iss >> a >> b >> c;
    cout << (f(a) + f(b) == f(c) ? "True" : "False") << endl;
  }
  return 0;
}
