#include <iostream>
#include <vector>
#include <iterator>
#include <algorithm>
using namespace std;

typedef string::const_iterator Iterator;

struct evaluator
{
  vector<int> all;
  vector<int> sets[5];

  vector<int> factor(Iterator& it, const Iterator& last) const
  {
    if (*it == '(') {
      ++it;
      const vector<int> r = expr(it, last);
      ++it;
      return r;
    } else {
      const int i = *it-'A';
      ++it;
      return sets[i];
    }
  }

  vector<int> term(Iterator& it, const Iterator& last) const
  {
    if (*it == 'c') {
      ++it;
      const vector<int> s = factor(it, last);
      vector<int> r;
      set_difference(all.begin(), all.end(), s.begin(), s.end(), back_inserter(r));
      return r;
    } else {
      return factor(it, last);
    }
  }

  vector<int> expr(Iterator& it, const Iterator& last) const
  {
    vector<int> r = term(it, last);
    while (it != last && (*it == 'u' || *it == 'i' || *it == 'd' || *it == 's')) {
      const char op = *it;
      ++it;
      const vector<int> l = term(it, last);
      vector<int> o;
      switch (op) {
        case 'u':
          set_union(r.begin(), r.end(), l.begin(), l.end(), back_inserter(o));
          break;
        case 'i':
          set_intersection(r.begin(), r.end(), l.begin(), l.end(), back_inserter(o));
          break;
        case 'd':
          set_difference(r.begin(), r.end(), l.begin(), l.end(), back_inserter(o));
          break;
        case 's':
          set_symmetric_difference(r.begin(), r.end(), l.begin(), l.end(), back_inserter(o));
          break;
      }
      swap(r, o);
    }
    return r;
  }
};

int main()
{
  while (!cin.eof()) {
    string name;
    int n;
    evaluator e;
    while (cin >> name >> n && name != "R") {
      vector<int>& s = e.sets[name[0]-'A'];
      for (int i = 0; i < n; i++) {
        int x;
        cin >> x;
        e.all.push_back(x);
        s.push_back(x);
      }
      sort(s.begin(), s.end());
    }
    sort(e.all.begin(), e.all.end());
    e.all.erase(unique(e.all.begin(), e.all.end()), e.all.end());

    string s;
    cin >> s;
    Iterator it = s.begin(), last = s.end();
    const vector<int> r = e.expr(it, last);
    if (r.empty()) {
      cout << "NULL" << endl;
    } else {
      for (vector<int>::const_iterator it = r.begin(); it != r.end(); ++it) {
        if (it != r.begin()) {
          cout << ' ';
        }
        cout << *it;
      }
      cout << endl;
    }

    cin.ignore();
    cin.peek();
  }
  return 0;
}
