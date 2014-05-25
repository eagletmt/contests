#include <iostream>
#include <cstdio>
using namespace std;

struct expr
{
  int x, c;
  expr(int a, int b) : x(a), c(b) {}
  static expr var(int a) { return expr(a, 0); }
  static expr lit(int a) { return expr(0, a); }

  expr& operator+=(const expr& e) { x += e.x; c += e.c; return *this;}
  expr& operator-=(const expr& e) { x -= e.x; c -= e.c; return *this;}
  expr& operator*=(const expr& e) { x = x*e.c + e.x*c; c = c * e.c; return *this; }
};

typedef string::const_iterator Iterator;

expr parse_expr(Iterator& it, const Iterator& last);

expr parse_factor(Iterator& it, const Iterator& last)
{
  if (*it == '(') {
    ++it;
    const expr e = parse_expr(it, last);
    ++it;
    return e;
  } else if (*it == 'x') {
    ++it;
    return expr::var(1);
  } else if (isdigit(*it)) {
    int n = 0;
    while (it != last && isdigit(*it)) {
      n = 10*n + *it-'0';
      ++it;
    }
    return expr::lit(n);
  } else {
    throw "parse error";
  }
}

expr parse_term(Iterator& it, const Iterator& last)
{
  expr l = parse_factor(it, last);
  while (it != last && (*it == '*')) {
    ++it;
    const expr r = parse_factor(it, last);
    l *= r;
  }
  return l;
}

expr parse_expr(Iterator& it, const Iterator& last)
{
  expr l = parse_term(it, last);
  while (it != last && (*it == '+' || *it == '-')) {
    const char op = *it;
    ++it;
    const expr r = parse_term(it, last);
    if (op == '+') {
      l += r;
    } else {
      l -= r;
    }
  }
  return l;
}

int main()
{
  string line;
  for (int Ti = 1; getline(cin, line); Ti++) {
    Iterator it = line.begin(), last = line.end();
    expr l = parse_expr(it, last);
    if (it == last || *it != '=') {
      throw "parse_error";
    }
    ++it;
    const expr r = parse_expr(it, last);
    l -= r;
    printf("Equation #%d\n", Ti);
    if (l.x == 0) {
      if (l.c == 0) {
        puts("Infinitely many solutions.");
      } else {
        puts("No solution.");
      }
    } else {
      printf("x = %.6f\n", double(-l.c)/l.x);
    }
    putchar('\n');
  }
  return 0;
}
