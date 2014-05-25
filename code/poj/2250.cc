#include <iostream>
#include <vector>
#include <map>
using namespace std;

struct renamer
{
  map<string,int> m;
  vector<string> v;
  int encode(const string& s)
  {
    map<string,int>::const_iterator it = m.find(s);
    if (it == m.end()) {
      const int id = m.size();
      m.insert(make_pair(s, id));
      v.push_back(s);
      return id;
    } else {
      return it->second;
    }
  }
  string decode(int id) const { return v[id]; }
};

int main()
{
  ios::sync_with_stdio(false);
  string s;
  while (cin >> s) {
    vector<int> xs, ys;
    renamer r;
    xs.push_back(r.encode(s));
    while (cin >> s && s != "#") {
      xs.push_back(r.encode(s));
    }
    while (cin >> s && s != "#") {
      ys.push_back(r.encode(s));
    }

    const int N = xs.size(), M = ys.size();
    vector<vector<int> > lcs(N+1, vector<int>(M+1, 0));
    vector<vector<pair<int,int> > > prev(N+1, vector<pair<int,int> >(M+1, make_pair(-1, -1)));
    for (int i = 1; i <= N; i++) {
      for (int j = 1; j <= M; j++) {
        int t = lcs[i-1][j-1] + (xs[i-1] == ys[j-1]);
        lcs[i][j] = max(t, max(lcs[i-1][j], lcs[i][j-1]));
        if (lcs[i][j] == t) {
          prev[i][j] = make_pair(i-1, j-1);
        } else if (lcs[i][j] == lcs[i-1][j]) {
          prev[i][j] = make_pair(i-1, j);
        } else {
          prev[i][j] = make_pair(i, j-1);
        }
      }
    }

    vector<int> seq;
    for (int i = N, j = M;;) {
      const int k = prev[i][j].first;
      const int l = prev[i][j].second;
      if (k == -1 || l == -1) {
        break;
      }
      if (k+1 == i && l+1 == j && lcs[k][l]+1 == lcs[i][j]) {
        seq.push_back(xs[i-1]);
      }
      i = k;
      j = l;
    }
    for (vector<int>::const_reverse_iterator it = seq.rbegin(); it != seq.rend(); ++it) {
      if (it != seq.rbegin()) {
        cout << ' ';
      }
      cout << r.decode(*it);
    }
    cout << endl;
  }
  return 0;
}
