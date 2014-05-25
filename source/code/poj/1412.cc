#include <iostream>
#include <string>
#include <cctype>
#include <cmath>
#include <cassert>
#include <algorithm>
using namespace std;

struct expr
{
  char op;
  const expr *lhs, *rhs;
  int c;
  char var;
  expr(int a) : op(0), lhs(0), rhs(0), c(a), var(0) {}
  expr(char v) : op(0), lhs(0), rhs(0), c(0), var(v) {}
  expr(char o, const expr *l, const expr *r)
    : op(o), lhs(l), rhs(r), c(0), var(0)
  {}
  ~expr() { delete lhs; delete rhs; }
};

typedef string::const_iterator Iterator;
void skip_white(Iterator& it, const Iterator& last);
const expr *parse_expr(Iterator& it, const Iterator& last);
const expr *parse_term(Iterator& it, const Iterator& last);
const expr *parse_exp(Iterator& it, const Iterator& last);
const expr *parse_factor(Iterator& it, const Iterator& last);

const expr *parse(const string& s)
{
  Iterator it = s.begin();
  const Iterator last = s.end();
  skip_white(it, last);
  return parse_expr(it, last);
}

void skip_white(Iterator& it, const Iterator& last)
{
  for (;it != last && *it == ' '; ++it);
}

const expr *parse_expr(Iterator& it, const Iterator& last)
{
  const expr *lhs = parse_term(it, last);
  skip_white(it, last);
  static const string a = "+-";
  while (it != last && a.find(*it) != string::npos) {
    const char op = *it;
    ++it;
    skip_white(it, last);
    const expr *rhs = parse_term(it, last);
    skip_white(it, last);
    lhs = new expr(op, lhs, rhs);
  }
  return lhs;
}

const expr *parse_term(Iterator& it, const Iterator& last)
{
  const expr *lhs = parse_exp(it, last);
  static const string a = "+-)";
  while (it != last && a.find(*it) == string::npos) {
    skip_white(it, last);
    const expr *rhs = parse_exp(it, last);
    skip_white(it, last);
    lhs = new expr('*', lhs, rhs);
  }
  return lhs;
}

const expr *parse_exp(Iterator& it, const Iterator& last)
{
  const expr *lhs = parse_factor(it, last);
  skip_white(it, last);
  if (*it == '^') {
    ++it;
    skip_white(it, last);
    const expr *rhs = parse_factor(it, last);
    skip_white(it, last);
    return new expr('^', lhs, rhs);
  } else {
    return lhs;
  }
}

const expr *parse_factor(Iterator& it, const Iterator& last)
{
  if (*it == '(') {
    ++it;
    skip_white(it, last);
    const expr *r = parse_expr(it, last);
    skip_white(it, last);
    assert(*it == ')');
    ++it;
    return r;
  } else {
    if (isdigit(*it)) {
      int c = 0;
      while (it != last && isdigit(*it)) {
        c = 10*c + *it-'0';
        ++it;
      }
      return new expr(c);
    } else {
      if (it != last && islower(*it)) {
        const char v = *it;
        ++it;
        return new expr(v);
      } else {
        throw "parse error";
      }
    }
  }
}

double eval(const expr *e, const int bs[26])
{
  if (!e->lhs) {
    if (e->var) {
      return bs[e->var-'a'];
    } else {
      return e->c;
    }
  } else {
    const double l = eval(e->lhs, bs);
    const double r = eval(e->rhs, bs);
    switch (e->op) {
      case '+': return l + r;
      case '-': return l - r;
      case '*': return l * r;
      case '^': return pow(l, r);
      default: throw "unknown operator";
    }
  }
}

bool equal(const expr *e1, const expr *e2)
{
  int binds[26];
  for (int t = 0; t < 26; t++) {
    for (int i = 0; i < 26; i++) {
      binds[i] = (5*t + i*7) % 26;
    }
    const double l = eval(e1, binds);
    const double r = eval(e2, binds);
    if (!(abs(l) < 1e-6 && abs(r) < 1e-6) && abs(abs(l / r) - 1.0) > 1e-6) {
      return false;
    }
  }
  return true;
}

int main()
{
  string s;
  while (getline(cin, s) && s != ".") {
    const expr *e1 = parse(s);
    while (getline(cin, s) && s != ".") {
      const expr *e2 = parse(s);
      cout << (equal(e1, e2) ? "yes" : "no") << endl;
      delete e2;
    }
    delete e1;
    cout << "." << endl;
  }
  return 0;
}
