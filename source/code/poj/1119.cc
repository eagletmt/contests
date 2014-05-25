#include <iostream>
#include <cstdio>
#include <sstream>
#include <vector>
#include <map>
#include <cmath>
#include <cctype>
using namespace std;

string f(const string& s)
{
  string t;
  for (string::const_iterator it = s.begin(); it != s.end(); ++it) {
    if (isalnum(*it)) {
      t += toupper(*it);
    }
  }
  return t;
}

void words(map<string, int>& dict, const string& line)
{
  istringstream iss(line);
  for (string w; iss >> w;) {
    const string v = f(w);
    if (!v.empty()) {
      ++dict[v];
    }
  }
}

int main()
{
  static const string TERM = "----------";
  map<string, int> dict;
  for (string line; getline(cin, line) && line != TERM;) {
    words(dict, line);
  }
  for (string line; getline(cin, line) && line != TERM;) {
    map<string, int> d;
    words(d, line);
    while (getline(cin, line) && line != TERM) {
      words(d, line);
    }
    double score = 0.0;
    for (map<string, int>::const_iterator it = dict.begin(); it != dict.end(); ++it) {
      score += sqrt(it->second * d[it->first]);
    }
    printf("%.2f\n", score);
  }
  return 0;
}
