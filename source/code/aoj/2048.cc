#include <iostream>
using namespace std;

int key(int x)
{
  int s = 0, m = 0;
  for (int i = 2; i <= x; i++) {
    if (x % i == 0) {
      s += i;
      m = i;
      while (x % i == 0) {
        x /= i;
      }
    }
  }
  return m - (s-m);
}

int main()
{
  int a, b;
  while (cin >> a >> b && a != 0) {
    cout << (key(a) > key(b) ? 'a' : 'b') << endl;
  }
  return 0;
}
