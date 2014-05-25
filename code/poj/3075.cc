#include <iostream>
#include <algorithm>
using namespace std;

bool ok(const string& s)
{
  const int X = count(s.begin(), s.end(), 'X');
  const int O = count(s.begin(), s.end(), 'O');
  if (!(X == O || X == O+1)) {
    return false;
  }

  static const int tbl[][3] = {
    {0, 4, 8},
    {2, 4, 6},
    {0, 1, 2},
    {3, 4, 5},
    {6, 7, 8},
    {0, 3, 6},
    {1, 4, 7},
    {2, 5, 8},
  };
  bool win[2] = {false, false};
  for (int d = 0; d < 8; d++) {
    if (s[tbl[d][0]] != '.'
        && s[tbl[d][0]] == s[tbl[d][1]]
        && s[tbl[d][1]] == s[tbl[d][2]]) {
      if (s[tbl[d][0]] == 'X') {
        win[0] = true;
      } else {
        win[1] = true;
      }
    }
  }
  if (win[0] && win[1]) {
    return false;
  } else if (!win[0] && win[1]) {
    return X == O;
  } else if (win[0] && !win[1]) {
    return X == O+1;
  } else {
    return count(s.begin(), s.end(), '.') == 0;
  }
}

int main()
{
  string s;
  while (cin >> s && s != "end") {
    cout << (ok(s) ? "" : "in") << "valid" << endl;
  }
  return 0;
}
