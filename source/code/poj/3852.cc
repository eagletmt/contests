#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct by_size
{
  bool operator()(const string& l, const string& r) const
  {
    if (l.size() == r.size()) {
      return l < r;
    } else {
      return l.size() < r.size();
    }
  }
};

int match(const string& s, const string& t)
{
  int c = 0;
  for (string::const_iterator it = s.begin(), jt = t.begin();
      it != s.end() && jt != t.end() && *it == *jt;
      ++it, ++jt, ++c);
  return c;
}

int main()
{
  ios::sync_with_stdio(false);
  int N;
  while (cin >> N && N != 0) {
    vector<string> v(N);
    for (int i = 0; i < N; i++) {
      cin >> v[i];
      reverse(v[i].begin(), v[i].end());
    }
    sort(v.begin(), v.end(), by_size());

    vector<string>::const_iterator last = v.begin();
    while (last != v.end() && last->size() == v[0].size()) {
      ++last;
    }
    const int len = v[0].size();
    int ans = len-1;
    for (vector<string>::const_iterator it = v.begin(); it != last; ++it) {
      for (vector<string>::const_iterator jt = it+1; jt != last; ++jt) {
        ans = min(ans, len-1-match(*it, *jt));
      }
    }
    cout << ans << endl;
  }
  return 0;
}
