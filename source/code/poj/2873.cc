#include <iostream>
#include <vector>
using namespace std;

typedef vector<int>::const_iterator Iterator;

int gcd(int a, int b)
{
  if (a < b) {
    swap(a, b);
  }
  int r;
  while ((r = a % b) != 0) {
    a = b;
    b = r;
  }
  return b;
}

int lcm(int a, int b) { return a*b/gcd(a, b); }

vector<string> parse(Iterator& it)
{
  const int tag = *it;
  ++it;
  switch (tag) {
    case 0:
      return vector<string>(1, "X");
    case 3:
      return vector<string>(1, " ");
    case 2:
      {
        const vector<string> left = parse(it);
        const vector<string> right = parse(it);
        const int h = lcm(left.size(), right.size());
        const int l = h / left.size(), r = h / right.size();
        vector<string> ret(h);
        for (int i = 0; i < h; i++) {
          for (int j = 0; j < l; j++) {
            ret[i] += left[i/l];
          }
          for (int j = 0; j < r; j++) {
            ret[i] += right[i/r];
          }
        }
        return ret;
      }
    case 1:
      {
        const vector<string> top = parse(it);
        const vector<string> under = parse(it);
        const int w = lcm(top[0].size(), under[0].size());
        const int t = w / top[0].size(), u = w / under[0].size();
        vector<string> ret;
        for (vector<string>::const_iterator jt = top.begin(); jt != top.end(); ++jt) {
          for (int j = 0; j < t; j++) {
            string s(w, ' ');
            for (int k = 0; k < w; k++) {
              s[k] = (*jt)[k/t];
            }
            ret.push_back(s);
          }
        }
        for (vector<string>::const_iterator jt = under.begin(); jt != under.end(); ++jt) {
          for (int j = 0; j < u; j++) {
            string s(w, ' ');
            for (int k = 0; k < w; k++) {
              s[k] = (*jt)[k/u];
            }
            ret.push_back(s);
          }
        }
        return ret;
      }
  }
  throw "err";
}

int main()
{
  for (string line; getline(cin, line);) {
    vector<int> v;
    for (string::size_type i = 0; i < line.size(); i += 2) {
      v.push_back(((line[i]-'0')<<1) | (line[i+1]-'0'));
    }
    Iterator it = v.begin();
    const vector<string> ans = parse(it);
    for (string::size_type i = 0; i < ans[0].size()+2; i++) {
      cout << "-";
    }
    cout << endl;
    for (vector<string>::const_iterator jt = ans.begin(); jt != ans.end(); ++jt) {
      cout << "|" << *jt << "|" << endl;
    }
    for (string::size_type i = 0; i < ans[0].size()+2; i++) {
      cout << "-";
    }
    cout << endl;
  }
  return 0;
}
