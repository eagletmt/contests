#include <iostream>
#include <deque>
#include <stack>
#include <algorithm>
using namespace std;

struct node
{
  deque<const node *> c;
  int idx;
  int need;
  node() : c(), idx(-1), need(1) {}

  void show() const
  {
    if (c.empty()) {
      cout << 'a';
    } else {
      const int N = c.size();
      for (int i = 0; i < N; i++) {
        c[(idx+i)%N]->show();
      }
      cout << N;
    }
  }
};

int main()
{
  ios::sync_with_stdio(false);
  string s;
  cin >> s;
  stack<node *> stk;
  for (string::const_iterator it = s.begin(); it != s.end(); ++it) {
    if (*it == 'a') {
      stk.push(new node());
    } else {
      const int n = *it - '0';
      node *t = new node();
      for (int i = 0; i < n; i++) {
        t->c.push_front(stk.top());
        stk.pop();
      }
      t->need = 100000000;
      for (int i = 0; i < n; i++) {
        int x = 0;
        for (int j = 0; j < n; j++) {
          x = max(x, t->c[(i+j)%n]->need + j);
        }
        if (x < t->need) {
          t->need = x;
          t->idx = i;
        }
      }
      stk.push(t);
    }
  }
  const node *root = stk.top();
  cout << root->need << endl;
  root->show();
  cout << endl;
  return 0;
}
