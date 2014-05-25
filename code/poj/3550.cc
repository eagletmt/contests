#include <iostream>
#include <algorithm>
#include <cctype>
using namespace std;

typedef string::const_iterator Iterator;

void digits(Iterator& it, const Iterator& last, int limit)
{
  for (int i = 0; i < limit && isdigit(*it) && it != last; ++i, ++it);
}

void header(Iterator& it, const Iterator& last)
{
  if (isupper(*it) || *it == '&' || *it == '#' || *it == '@') {
    ++it;
    if (isupper(*it)) {
      ++it;
    }
    digits(it, last, 20);
  } else {
    throw __LINE__;
  }
}

void command(Iterator& it, const Iterator& last)
{
  const Iterator save = it;
  header(it, last);
  if (*it == '=') {
    ++it;
    digits(it, last, 4);
  }
  cout << string(save, it) << endl;
}

int main()
{
  string s;
  getline(cin, s);
  Iterator it = s.begin()+2, last = s.end();
  while (it != last) {
    command(it, last);
  }
  return 0;
}
