#include <iostream>
#include <vector>
#include <sstream>
#include <set>
#include <functional>
#include <cassert>
using namespace std;

typedef string::const_iterator Iterator;

Iterator matching_paren(Iterator it, const Iterator& last)
{
  for (int d = 1; it != last; ++it) {
    if (*it == ')') {
      --d;
      if (d == 0) {
        return it;
      }
    } else if (*it == '(') {
      ++d;
    }
  }
  throw "paren mismatch";
}

set<int> eval(const string& str)
{
  vector<string> terms;
  vector<char> ops;
  string term;
  for (string::const_iterator it(str.begin()), end = str.end(); it != end; ++it) {
    if ('0' <= *it && *it <= '9') {
      term += *it;
    } else if (*it == '(') {
      if (!term.empty()) {
        terms.push_back(term);
      }
      term = "";
      Iterator l = matching_paren(it+1, end);
      term = string(it, l+1);
      it = l;
    } else {
      if (!term.empty()) {
        terms.push_back(term);
      }
      term = "";
      assert(*it == '+' || *it == '-' || *it == '*' || *it == '/');
      ops.push_back(*it);
    }
  }
  terms.push_back(term);
  assert(ops.size()+1 == terms.size());

  if (ops.empty()) {
    if (terms[0][0] == '(') {
      return eval(terms[0].substr(1, terms[0].size()-2));
    } else {
      set<int> s;
      istringstream iss(terms[0]);
      int x;
      iss >> x;
      s.insert(x);
      return s;
    }
  } else {
    set<int> s;
    for (vector<char>::size_type i = 0; i < ops.size(); i++) {
      string lhs;
      for (vector<string>::size_type j = 0; j <= i; j++) {
        if (j != 0) {
          lhs += ops[j-1];
        }
        lhs += terms[j];
      }
      const set<int> l = eval(lhs);
      string rhs;
      for (vector<string>::size_type j = i+1; j < terms.size(); j++) {
        if (j != i+1) {
          rhs += ops[j-1];
        }
        rhs += terms[j];
      }
      const set<int> r = eval(rhs);
      for (set<int>::const_iterator jt(l.begin()); jt != l.end(); ++jt) {
        for (set<int>::const_iterator kt(r.begin()); kt != r.end(); ++kt) {
          switch (ops[i]) {
            case '+': s.insert(*jt + *kt);  break;
            case '-': s.insert(*jt - *kt);  break;
            case '*': s.insert(*jt * *kt);  break;
            case '/': if (*kt != 0) { s.insert(*jt / *kt); }  break;
          }
        }
      }
    }
    return s;
  }
}

int main()
{
  for (string s; cin >> s && s != "#";) {
    cout << eval(s).size() << endl;
  }
  return 0;
}
