#include <iostream>
#include <vector>
#include <cctype>
#include <cassert>
using namespace std;

struct formula
{
  char var;
  char op;
  const formula *lhs, *rhs;
  formula(char v) : var(v), op(0), lhs(0), rhs(0) {}
  formula(char o, const formula *l, const formula *r = 0)
    : var(0), op(o), lhs(l), rhs(r) {}
  ~formula() { delete lhs;  delete rhs; }
  bool eval(bool bs[5]) const
  {
    if (var) {
      return bs[var-'p'];
    } else {
      switch (op) {
        case 'K': return lhs->eval(bs) && rhs->eval(bs);
        case 'A': return lhs->eval(bs) || rhs->eval(bs);
        case 'N': return !lhs->eval(bs);
        case 'C': return !lhs->eval(bs) || rhs->eval(bs);
        case 'E': return lhs->eval(bs) == rhs->eval(bs);
        default: throw "unknown operator";
      }
    }
  }
};

typedef string::const_iterator Iterator;
const formula *parse(Iterator& it, const Iterator& last)
{
  assert(it != last);
  if (islower(*it)) {
    const char v = *it;
    ++it;
    return new formula(v);
  } else if (*it == 'N') {
    ++it;
    return new formula('N', parse(it, last));
  } else {
    const char op = *it;
    ++it;
    const formula *l = parse(it, last);
    const formula *r = parse(it, last);
    return new formula(op, l, r);
  }
}

bool tautology(const formula *f)
{
  for (int s = 0; s < (1<<5); s++) {
    bool bs[5];
    for (int i = 0; i < 5; i++) {
      bs[i] = (s & (1<<i)) != 0;
    }
    if (!f->eval(bs)) {
      return false;
    }
  }
  return true;
}

int main()
{
  string s;
  while (cin >> s && s != "0") {
    Iterator it = s.begin();
    const Iterator last = s.end();
    const formula *f = parse(it, last);
    cout << (tautology(f) ? "tautology" : "not") << endl;
    delete f;
  }
}
