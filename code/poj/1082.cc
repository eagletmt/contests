#include <iostream>
using namespace std;
static const int YEAR = 2001-1900, MON = 11, MDAY = 4;

bool overrun(int year, int mon, int mday)
{
  if (year > YEAR) {
    return true;
  } else if (year < YEAR) {
    return false;
  }
  if (mon > MON) {
    return true;
  } else if (mon < MON) {
    return false;
  }
  if (mday > MDAY) {
    return true;
  }
  return false;
}

bool leap(int y)
{
  y += 1900;
  if (y % 400 == 0) {
    return true;
  } else if (y % 100 == 0) {
    return false;
  } else if (y % 4 == 0) {
    return true;
  } else {
    return false;
  }
}

int days(int y, int m)
{
  static const int t[] = {-1, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
  if (m == 2) {
    return t[m] + leap(y);
  } else {
    return t[m];
  }
}

void fix(int& y, int& m, int& d)
{
  if (d > days(y, m)) {
    d = 1;
    ++m;
  }
  if (m > 12) {
    m = 1;
    ++y;
  }
}

int memo[YEAR+1][13][40];

bool solve(int year, int mon, int mday)
{
  if (year == YEAR && mon == MON && mday == MDAY) {
    return false;
  } else if (overrun(year, mon, mday)) {
    throw "err";
  } else {
    int& ans = memo[year][mon][mday];
    if (ans != -1) {
      return ans;
    }
    int y = year, m = mon, d = mday+1;
    fix(y, m, d);
    if (!solve(y, m, d)) {
      return ans = true;
    }
    y = year, m = mon+1, d = mday;
    fix(y, m, d);
    if (d == mday && !overrun(y, m, d) && !solve(y, m, d)) {
      return ans = true;
    }
    return ans = false;
  }
}

int main()
{
  for (int i = 0; i <= YEAR; i++) {
    for (int j = 1; j <= 12; j++) {
      for (int k = 1; k < 40; k++) {
        memo[i][j][k] = -1;
      }
    }
  }
  int T;
  cin >> T;
  while (T-- > 0) {
    int y, m, d;
    cin >> y >> m >> d;
    y -= 1900;
    cout << (solve(y, m, d) ? "YES" : "NO") << endl;
  }
  return 0;
}
