#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct tree {
  int v;
  const tree *left, *right;
  tree(int v_, const tree *l, const tree *r) : v(v_), left(l), right(r) {}
  ~tree() { delete left; delete right; }

  bool has(int n) const
  {
    if (left == 0 && right == 0) {
      return n == v;
    } else {
      return (left && left->has(n - v)) || (right && right->has(n - v));
    }
  }
};

typedef string::const_iterator Iterator;
const tree* parse(Iterator& it, const Iterator& last)
{
  if (it == last) {
    throw "eof";
  }
  if (*it != '(') {
    throw "parse error";
  }

  ++it;
  if (*it == ')') {
    ++it;
    return 0;
  } else {
    int v = 0;
    bool neg = false;
    if (*it == '-') {
      neg = true;
      ++it;
    }
    while (*it != '(') {
      v = 10*v + (*it - '0');
      ++it;
    }
    if (neg) {
      v = -v;
    }
    const tree *left = parse(it, last);
    const tree *right = parse(it, last);
    if (*it != ')') {
      throw "parse error";
    }
    ++it;
    return new tree(v, left, right);
  }
}

int main()
{
  int n;
  while (cin >> n) {
    string buf;
    cin >> buf;
    int kakko = count(buf.begin(), buf.end(), '(');
    kakko -= count(buf.begin(), buf.end(), ')');
    while (kakko > 0) {
      string s;
      cin >> s;
      kakko += count(s.begin(), s.end(), '(');
      kakko -= count(s.begin(), s.end(), ')');
      buf += s;
    }
    Iterator it = buf.begin(), last = buf.end();
    const tree *t = parse(it, last);
    if (t) {
      cout << (t->has(n) ? "yes" : "no") << endl;
    } else {
      cout << "no" << endl;
    }
    delete t;
  }
  return 0;
}
