#include <iostream>
#include <sstream>
#include <vector>
#include <algorithm>
using namespace std;

struct poly
{
  int cs[15];
  poly() { fill_n(cs, 15, 0); }
  poly& operator+=(const poly& p)
  {
    for (int i = 0; i <= 10; i++) {
      cs[i] += p.cs[i];
    }
    return *this;
  }
  poly operator*(const poly& p) const
  {
    poly ans;
    for (int i = 0; i <= 10; i++) {
      for (int j = 0; i+j <= 10; j++) {
        ans.cs[i+j] += cs[i] * p.cs[j];
      }
    }
    return ans;
  }
};
ostream& operator<<(ostream& os, const poly& p)
{
  bool first = true;
  for (int i = 10; i >= 0; i--) {
    if (p.cs[i] != 0) {
      if (!first) {
        os << '+';
      }

      if (p.cs[i] == 1 && i != 0) {
      } else {
        os << p.cs[i];
        if (i != 0) {
          os << "*";
        }
      }

      if (i != 0) {
        os << "n";
        if (i != 1) {
          os << "^" << i;
        }
      }
      first = false;
    }
  }
  if (first) {
    os << 0;
  }
  return os;
}

typedef vector<string>::const_iterator Iterator;
int read(const string& s)
{
  istringstream iss(s);
  int n;
  iss >> n;
  return n;
}

poly statements(Iterator& it);
poly statement(Iterator& it)
{
  if (*it == "OP") {
    ++it;
    poly p;
    p.cs[0] = read(*it);
    ++it;
    return p;
  } else if (*it == "LOOP") {
    ++it;
    const string s = *it;
    ++it;
    poly p;
    if (s == "n") {
      p.cs[1] = 1;
    } else {
      p.cs[0] = read(s);
    }
    const poly q = statements(it);
    if (*it != "END") { throw "statement-loop"; }
    ++it;
    const poly ans = p * q;
    return ans;
  } else {
    throw "statement";
  }
}

poly statements(Iterator& it)
{
  poly p;
  p.cs[0] = 0;
  while (*it == "LOOP" || *it == "OP") {
    p += statement(it);
  }
  return p;
}

poly program(Iterator& it)
{
  if (*it != "BEGIN") { throw "program-begin"; }
  ++it;
  const poly p = statements(it);
  if (*it != "END") { throw "program-end"; }
  ++it;
  return p;
}

int main()
{
  int T;
  cin >> T;
  vector<string> tokens;
  for (string tok; cin >> tok;) {
    tokens.push_back(tok);
  }
  Iterator it = tokens.begin();
  for (int Ti = 1; Ti <= T; Ti++) {
    cout << "Program #" << Ti << endl;
    const poly p = program(it);
    cout << "Runtime = " << p << endl;
    cout << endl;
  }
  return 0;
}
