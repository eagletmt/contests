#include <iostream>
#include <vector>
#include <map>
using namespace std;
typedef string::const_iterator Iterator;

struct error {};
struct parse_error {
  Iterator it;
  parse_error() {}
  parse_error(const Iterator& a) : it(a) {}
};

struct array
{
  int capacity;
  map<int,int> vals;

  void assign(int idx, int val)
  {
    if (idx < 0 || capacity <= idx) {
      //cerr << "idx = " << idx << endl;
      throw error();
    }
    vals[idx] = val;
  }

  int get(int idx)
  {
    if (!vals.count(idx)) {
      throw error();
    }
    return vals[idx];
  }
};

int number(Iterator& it, const Iterator& last)
{
  int n = 0;
  while (isdigit(*it) && it != last) {
    n = 10*n + *it-'0';
    ++it;
  }
  return n;
}

int expr(map<char,array>& env, Iterator& it, const Iterator& last)
{
  Iterator save = it;
  int n = number(it, last);
  if (it != save) {
    return n;
  }
  char name = *it;
  ++it;
  if (*it != '[') {
    throw parse_error(it);
  }
  ++it;
  int v = expr(env, it, last);
  if (*it != ']') {
    throw parse_error(it);
  }
  ++it;
  if (!env.count(name)) {
    throw error();
  }
  return env[name].get(v);
}

void declare(map<char,array>& env, Iterator& it, const Iterator& last)
{
  char name = *it;
  ++it;
  if (*it != '[') {
    throw parse_error(it);
  }
  ++it;
  int n = number(it, last);
  if (*it != ']') {
    throw parse_error(it);
  }
  ++it;
  if (it != last) {
    throw parse_error(it);
  }
  env[name].capacity = n;
}

void assignment(map<char,array>& env, Iterator& it, const Iterator& last)
{
  char name = *it;
  ++it;
  if (*it != '[') {
    throw parse_error();
  }
  ++it;
  int n = expr(env, it, last);
  if (*it != ']') {
    throw parse_error();
  }
  ++it;
  if (*it != '=') {
    throw parse_error();
  }
  ++it;
  int v = expr(env, it, last);
  env[name].assign(n, v);
  if (it != last) {
    throw parse_error();
  }
}

int eval(map<char,array>& env, Iterator& it, const Iterator& last)
{
  Iterator save = it;
  try {
    declare(env, it, last);
  } catch (const parse_error& err) {
    it = save;
    assignment(env, it, last);
  }
}

int main()
{
  string line;
  while (getline(cin, line) && line != ".") {
    vector<string> ls(1, line);
    while (getline(cin, line) && line != ".") {
      ls.push_back(line);
    }

    int n = 1;
    try {
      map<char, array> env;
      for (vector<string>::const_iterator it(ls.begin()); it != ls.end(); ++it) {
        Iterator jt = it->begin(), last = it->end();
        eval(env, jt, last);
        ++n;
      }
      cout << "0" << endl;
    } catch (const error&) {
      cout << n << endl;
    }
  }
  return 0;
}
