#include <iostream>
#include <algorithm>
using namespace std;

bool ws_p(char c) { return c == ' ' || c == '\t'; }
bool digit_p(char c) { return '0' <= c && c <= '9'; }
bool op_p(char c) { return c == '+' || c == '-' || c == '*'; }

typedef string::const_iterator Iterator;

struct expr
{
  char c;
  int n;
  expr *l, *r;
  expr(int x) : c(0), n(x), l(0), r(0) {}
  expr(char x) : c(x), n(0), l(0), r(0) {}
  expr(char o, expr *a, expr *b) : c(o), n(0), l(a), r(b) {}
  ~expr() { delete l; delete r; }
  int eval(const int *env) const
  {
    switch (c) {
      case 0: return n;
      case '+': return l->eval(env) + r->eval(env);
      case '-': return l->eval(env) - r->eval(env);
      case '*': return l->eval(env) * r->eval(env);
      default:  return env[c-'a'];
    }
  }
};

expr *parse_expr(Iterator& it, const Iterator& last);

expr *parse_term(Iterator& it, const Iterator& last)
{
  if (*it == '(') {
    ++it;
    expr *e = parse_expr(it, last);
    if (*it != ')') {
      throw ")";
    }
    ++it;
    return e;
  } else if (digit_p(*it)) {
    expr *e = new expr(int(*it-'0'));
    ++it;
    return e;
  } else {
    expr *e = new expr(char(*it));
    ++it;
    return e;
  }
}

expr *parse_expr(Iterator& it, const Iterator& last)
{
  expr *l = parse_term(it, last);
  while (it != last && op_p(*it)) {
    char op = *it;
    ++it;
    expr *r = parse_term(it, last);
    l = new expr(op, l, r);
  }
  return l;
}

struct xorshift
{
  unsigned x, y, z, w;
  xorshift() : x(123456789), y(362436069), z(521288629), w(88675123) {}
  unsigned operator()()
  {
    unsigned t = x ^ (x << 11);
    x = y; y = z; z = w;
    return (w = (w ^ (w >> 19)) ^ (t ^ (t >> 8))) % 100;
  }
};

bool same_p(expr *a, expr *b)
{
  xorshift rng;
  for (int i = 0; i < 100; i++) {
    int env[26];
    for (int j = 0; j < 26; j++) {
      env[j] = rng();
    }
    if (a->eval(env) != b->eval(env)) {
      return false;
    }
  }
  return true;
}

int main()
{
  int N;
  cin >> N;
  cin.ignore();
  while (N-- > 0) {
    expr *e[2];
    for (int i = 0; i < 2; i++) {
      string s;
      getline(cin, s);
      s.erase(remove_if(s.begin(), s.end(), ws_p), s.end());
      Iterator it = s.begin(), last = s.end();
      e[i] = parse_expr(it, last);
    }
    cout << (same_p(e[0], e[1]) ? "YES" : "NO") << endl;
    delete e[0];
    delete e[1];
  }
  return 0;
}
