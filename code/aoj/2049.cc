#include <iostream>
#include <vector>
using namespace std;

int gcd(int a, int b)
{
  if (a < b) {
    swap(a, b);
  }
  for (int r; (r = a % b) != 0;) {
    a = b;
    b = r;
  }
  return b;
}

int main()
{
  int x, y;
  while (cin >> x >> y && x != 0) {
    const int g = gcd(x, y);
    x /= g; y /= g;
    vector<int> seen(y, -1);
    seen[x] = 0;
    for (int c = 1;; c++) {
      x = (10*x) % y;
      if (x == 0) {
        cout << c << " 0" << endl;
        break;
      } else if (seen[x] != -1) {
        cout << seen[x] << ' ' << c-seen[x] << endl;
        break;
      }
      seen[x] = c;
    }
  }
  return 0;
}
