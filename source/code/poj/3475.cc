#include <iostream>
using namespace std;

int f(long long x, long long y)
{
  int c = 0;
  while (y > x) {
    x *= 2LL;
    ++c;
  }
  return c;
}

int main()
{
  int a, b, c, d;
  while (cin >> a >> b >> c >> d) {
    cout << min(f(a, c) + f(b, d), f(b, c) + f(a, d)) << endl;
  }
  return 0;
}
