#include <iostream>
#include <deque>
using namespace std;

struct tree
{
  string name;
  deque<tree> cs;
  tree(const string& s) : name(s), cs() {}

  void print(int depth = 0) const
  {
    for (int i = 0; i < depth; i++) {
      cout << "+";
    }
    cout << name << endl;
    for (deque<tree>::const_iterator it(cs.begin()); it != cs.end(); ++it) {
      it->print(depth+1);
    }
  }

  void fire(const string& victim)
  {
    if (name == victim) {
      if (!cs.empty()) {
        swap(name, cs[0].name);
        cs[0].fire(victim);
      }
    } else {
      for (deque<tree>::iterator it = cs.begin(); it != cs.end(); ++it) {
        it->fire(victim);
      }
    }
    for (deque<tree>::iterator it = cs.begin(); it != cs.end(); ++it) {
      if (it->name == victim) {
        cs.erase(it);
        return;
      }
    }
  }

  bool hire(const string& boss, const string& s)
  {
    if (boss == name) {
      cs.push_back(tree(s));
      return true;
    } else {
      for (deque<tree>::iterator it = cs.begin(); it != cs.end(); ++it) {
        if (it->hire(boss, s)) {
          return true;
        }
      }
    }
    return false;
  }
};

int main()
{
  string name;
  cin >> name;
  tree root(name);
  while (cin >> name) {
    if (name == "print") {
      root.print();
      cout << "------------------------------------------------------------" << endl;
    } else if (name == "fire") {
      cin >> name;
      root.fire(name);
    } else {
      string t;
      cin >> t >> t;
      root.hire(name, t);
    }
  }
  return 0;
}
