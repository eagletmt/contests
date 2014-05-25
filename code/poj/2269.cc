#include <iostream>
#include <algorithm>
using namespace std;

typedef string::const_iterator Iterator;

string eval(Iterator& it, const Iterator& last);
string eval_term(Iterator& it, const Iterator& last);
string eval_factor(Iterator& it, const Iterator& last);

string eval_factor(Iterator& it, const Iterator& last)
{
  if (it == last) {
    throw "exhausted";
  } else if (*it == '{') {
    ++it;
    Iterator jt = find(it, last, '}');
    const string r(it, jt);
    it = jt+1;
    return r;
  } else if (*it == '(') {
    ++it;
    const string r = eval(it, last);
    if (it == last || *it != ')') {
      throw "unmatched paren";
    }
    ++it;
    return r;
  } else {
    throw "unknown term";
  }
}

string eval_term(Iterator& it, const Iterator& last)
{
  string r = eval_factor(it, last);
  while (it != last && *it == '*') {
    ++it;
    const string l = eval_factor(it, last);
    string t;
    set_intersection(r.begin(), r.end(), l.begin(), l.end(), back_inserter(t));
    r = t;
  }
  return r;
}

string eval(Iterator& it, const Iterator& last)
{
  string r = eval_term(it, last);
  while (it != last && (*it == '+' || *it == '-')) {
    const char op = *it;
    ++it;
    const string l = eval_term(it, last);
    string t;
    switch (op) {
      case '+':
        set_union(r.begin(), r.end(), l.begin(), l.end(), back_inserter(t));
        break;
      case '-':
        set_difference(r.begin(), r.end(), l.begin(), l.end(), back_inserter(t));
        break;
      default:
        throw "unknown operator";
    }
    r = t;
  }
  return r;
}

int main()
{
  string line;
  while (cin >> line) {
    Iterator it = line.begin(), last = line.end();
    cout << "{" << eval(it, last) << "}" << endl;
  }
  return 0;
}
