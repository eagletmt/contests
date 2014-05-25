#include <iostream>
#include <vector>
#include <set>
#include <algorithm>
using namespace std;

string gsub(string str, const string& pat, const string& sub)
{
  for (string::size_type i = 0; i < str.size();) {
    const string::size_type p = str.find(pat, i);
    if (p == string::npos) {
      break;
    }
    str.replace(p, pat.size(), sub);
    i = p + sub.size();
  }
  return str;
}

set<string> visited;
vector<pair<string,string> > subs;
string target;
int ans;
void dfs(const string& str, int depth)
{
  if (str == target) {
    ans = min(ans, depth);
    return;
  }
  if (str.size() >= target.size() || visited.count(str)) {
    return;
  }
  visited.insert(str);
  for (vector<pair<string,string> >::const_iterator it = subs.begin(); it != subs.end(); ++it) {
    dfs(gsub(str, it->first, it->second), depth+1);
  }
}

int main()
{
  int N;
  while (cin >> N && N != 0) {
    subs.resize(N);
    for (int i = 0; i < N; i++) {
      cin >> subs[i].first >> subs[i].second;
    }
    string str;
    cin >> str >> target;

    static const int INF = 10000;
    visited.clear();
    ans = INF;
    dfs(str, 0);
    cout << (ans == INF ? -1 : ans) << endl;
  }
  return 0;
}
