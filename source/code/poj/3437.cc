#include <iostream>
#include <vector>
using namespace std;

pair<int,int> parse(string::const_iterator& it, const string::const_iterator& last)
{
  int h1 = 0, h2 = 0;
  int i = 0;
  while (it != last && *it == 'd') {
    ++it;
    const pair<int,int> r = parse(it, last);
    h1 = max(h1, r.first + 1);
    h2 = max(h2, ++i + r.second);
  }
  if (it != last && *it == 'u') {
    ++it;
  }
  return make_pair(h1, h2);
}

int main()
{
  ios::sync_with_stdio(false);
  string line;
  for (int Ti = 1; getline(cin, line) && line != "#"; Ti++) {
    string::const_iterator it = line.begin(), last = line.end();
    const pair<int,int> r = parse(it, last);
    cout << "Tree " << Ti << ": " << r.first << " => " << r.second << endl;
  }
  return 0;
}
