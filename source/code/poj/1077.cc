#include <iostream>
#include <cstring>
#include <map>
#include <queue>
#include <algorithm>
using namespace std;

struct fixed_string
{
  char buf[9];
  fixed_string() {}
  fixed_string(const fixed_string& s) { memcpy(buf, s.buf, 9); }
  char& operator[](int n) { return buf[n]; }
  char operator[](int n) const { return buf[n]; }
  bool operator<(const fixed_string& s) const { return memcmp(buf, s.buf, 9) < 0; }
};

int h(const fixed_string& s)
{
  int d = 0;
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      const int x = s[3*i+j]-'1';
      d += abs(x/3 - i) + abs(x%3 - j);
    }
  }
  return d;
}

bool finish(const fixed_string& s)
{
  return h(s) == 0;
}

fixed_string f(fixed_string s, int di, int dj)
{
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      char& t = s[3*i+j];
      if (t == '9') {
        const int k = i + di;
        const int l = j + dj;
        if (0 <= k && k < 3 && 0 <= l && l < 3) {
          swap(t, s[3*k+l]);
          return s;
        } else {
          return s;
        }
      }
    }
  }
  throw "unexpected";
}

int main()
{
  fixed_string init;
  for (int i = 0; i < 9; i++) {
    char c;
    cin >> c;
    if (c == 'x') {
      c = '9';
    }
    init[i] = c;
  }

  priority_queue<pair<int,fixed_string> > q;
  q.push(make_pair(-h(init), init));
  map<fixed_string,string> dist;
  dist.insert(make_pair(init, ""));
  while (!q.empty()) {
    const fixed_string s = q.top().second;
    q.pop();
    if (finish(s)) {
      cout << dist[s] << endl;
      return 0;
    }
    for (int d = 0; d < 4; d++) {
      static const int di[] = {0, 0, -1, 1};
      static const int dj[] = {1, -1, 0, 0};
      const fixed_string t = f(s, di[d], dj[d]);
      static const char tbl[] = "rlud";
      const string cc = dist[s] + tbl[d];
      const int hh = cc.size() + h(t);
      if (!dist.count(t)) {
        dist.insert(make_pair(t, cc));
        q.push(make_pair(-hh, t));
      }
    }
  }
  cout << "unsolvable" << endl;
  return 0;
}
