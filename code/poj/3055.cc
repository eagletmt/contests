#include <iostream>
using namespace std;

bool ok(const int *a, const int *b)
{
  for (int i = 0; i < 10; i++) {
    if ((a[i] == 0) != (b[i] == 0)) {
      return false;
    }
  }
  return true;
}

void countup(int *a, const string& s)
{
  for (string::const_iterator it = s.begin(); it != s.end(); ++it) {
    ++a[*it-'0'];
  }
}

bool friends(const string& x, const string& y)
{
  int a[10] = {0}, b[10] = {0};
  countup(a, x);
  countup(b, y);
  return ok(a, b);
}

bool almost_friends(const string& x, const string& y)
{
  int a[10] = {0}, b[10] = {0};
  countup(a, x);
  countup(b, y);

  for (string::const_iterator it = x.begin(); it != x.end() && it+1 != x.end(); ++it) {
    const int s = *it-'0';
    const int t = *(it+1)-'0';
    if (s < 9 && t > 0) {
      --a[s];
      --a[t];
      ++a[s+1];
      ++a[t-1];
      if (ok(a, b)) {
        return true;
      }
      ++a[s];
      ++a[t];
      --a[s+1];
      --a[t-1];
    }
    if (s > 0 && t < 9 && !(s == 1 && it == x.begin())) {
      --a[s];
      --a[t];
      ++a[s-1];
      ++a[t+1];
      if (ok(a, b)) {
        return true;
      }
      ++a[s];
      ++a[t];
      --a[s-1];
      --a[t+1];
    }
  }
  return false;
}

int main()
{
  int T;
  cin >> T;
  while (T-- > 0) {
    string x, y;
    cin >> x >> y;
    if (friends(x, y)) {
      cout << "friends" << endl;
    } else if (almost_friends(x, y) || almost_friends(y, x)) {
      cout << "almost friends" << endl;
    } else {
      cout << "nothing" << endl;
    }
  }
  return 0;
}
