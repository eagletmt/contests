#include <iostream>
#include <cmath>
using namespace std;

int tetra(int m) { return m*(m+1)*(m+2)/6; }

int main()
{
  int N;
  while (cin >> N && N != 0) {
    int ans = 0;
    for (int m = 0; tetra(m) <= N; m++) {
      const int n = cbrt(N - tetra(m));
      ans = max(ans, n*n*n + tetra(m));
    }
    cout << ans << endl;
  }
  return 0;
}
