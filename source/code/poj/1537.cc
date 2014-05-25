#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;

typedef string::const_iterator Iterator;

bool sign(Iterator& it, const Iterator& last)
{
  if (it == last) {
    return false;
  } else if (*it == '+' || *it == '-') {
    ++it;
    return true;
  } else {
    return false;
  }
}

void digits(Iterator& it, const Iterator& last)
{
  while (it != last && '0' <= *it && *it <= '9') {
    ++it;
  }
}

bool ok(const string& s)
{
  Iterator it = s.begin(), last = s.end();
  sign(it, last);
  Iterator save = it;
  digits(it, last);
  if (it == save) {
    return false;
  }
  if (*it == '.') {
    ++it;
    save = it;
    digits(it, last);
    if (it == save) {
      return false;
    }
  } else if (it == last) {
    return false;
  }

  if (it == last) {
    return true;
  } else if (*it == 'e' || *it == 'E') {
    ++it;
    sign(it, last);
    save = it;
    digits(it, last);
    if (it == save) {
      return false;
    }
    return it == last;
  } else {
    return false;
  }
}

int main()
{
  for (string s; getline(cin, s) && s != "*";) {
    s.erase(remove(s.begin(), s.end(), ' '), s.end());
    cout << s << " is " << (ok(s) ? "" : "il") << "legal." << endl;
  }
  return 0;
}
