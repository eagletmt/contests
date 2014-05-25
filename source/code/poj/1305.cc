#include <iostream>
#include <algorithm>
using namespace std;

int gcd(int a, int b)
{
  int r;
  while ((r = a % b) != 0) {
    a = b;
    b = r;
  }
  return b;
}

int main()
{
  int N;
  while (cin >> N) {
    int x = 0;
    static bool v[1000001];
    fill_n(v, 1000000, false);
    for (int n = 1; n*n < N; n++) {
      for (int m = n+1; n*n + m*m <= N; m += 2) {
        if (gcd(m, n) == 1) {
          ++x;
          const int a = m*m - n*n, b = 2*m*n, c = m*m + n*n;
          for (int d = a, e = b, f = c; f <= N; d += a, e += b, f += c) {
            v[d] = v[e] = v[f] = true;
          }
        }
      }
    }
    int y = 0;
    for (int i = 1; i <= N; i++) {
      if (!v[i]) {
        ++y;
      }
    }
    cout << x << ' ' << y << endl;
  }
  return 0;
}
