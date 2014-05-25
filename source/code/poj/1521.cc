#include <iostream>
#include <cstdio>
#include <queue>
#include <functional>
#include <algorithm>
using namespace std;

struct node
{
  int c;
  node *left, *right;
  node(int a) : c(a), left(0), right(0) {}
  node(node *l, node *r) : c(0), left(l), right(r) {}
  ~node() { delete left; delete right; }
  void assign(int *d, int x = 0) const
  {
    if (c == 0) {
      left->assign(d, x+1);
      right->assign(d, x+1);
    } else {
      d[c] = x;
    }
  }
};

int huffman(const string& s)
{
  static int a[256];
  fill_n(a, 256, 0);
  for (string::const_iterator it = s.begin(); it != s.end(); ++it) {
    ++a[int(*it)];
  }
  priority_queue<pair<int,node*>, vector<pair<int,node*> >, greater<pair<int,node*> > > q;
  for (int i = 0; i < 256; i++) {
    if (a[i] > 0) {
      q.push(make_pair(a[i], new node(i)));
    }
  }
  if (q.size() == 1) {
    return q.top().first;
  }
  while (q.size() > 1) {
    const pair<int,node*> l = q.top();  q.pop();
    const pair<int,node*> r = q.top();  q.pop();
    q.push(make_pair(l.first + r.first, new node(l.second, r.second)));
  }
  static int d[256];
  node *root = q.top().second;
  root->assign(d);
  delete root;
  int ans = 0;
  for (int i = 0; i < 256; i++) {
    ans += a[i] * d[i];
  }
  return ans;
}

int main()
{
  for (string s; cin >> s && s != "END";) {
    int x = huffman(s);
    printf("%lu %d %.1f\n", 8*s.size(), x, 8.0*s.size()/x);
  }
  return 0;
}
