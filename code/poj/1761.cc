#include <iostream>
#include <cstdio>
#include <map>
using namespace std;

int main()
{
  int N;
  cin >> N;
  map<char, map<string, int> > accepted;
  map<char, map<string, int> > submits;
  for (int i = 0; i < N; i++) {
    int t;
    string s;
    char p, r;
    cin >> t >> s >> p >> r;
    if (!accepted[p].count(s)) {
      ++submits[p][s];
      if (r == 'A') {
        accepted[p].insert(make_pair(s, t));
      }
    }
  }

  for (char p = 'A'; p <= 'I'; p++) {
    const map<string, int>& ac = accepted[p];
    const map<string, int>& s = submits[p];
    const int n = ac.size();
    printf("%c %d", p, n);
    if (n == 0) {
      putchar('\n');
    } else {
      int elapsed = 0;
      int subs = 0;
      for (map<string, int>::const_iterator it = ac.begin(); it != ac.end(); ++it) {
        elapsed += it->second;
        subs += s.find(it->first)->second;
      }
      printf(" %.2f %.2f\n", double(subs)/n, double(elapsed)/n);
    }
  }
  return 0;
}
