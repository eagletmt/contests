#include <iostream>
#include <vector>
using namespace std;

int main(void)
{
  static const int N = 100, M = 100;

  vector<vector<int> > c(N+1, vector<int>(M+1, 1));
  for (int i = 2; i <= N; i++) {
    for (int j = 1; j < i; j++) {
      c[i][j] = c[i-1][j] + c[i-1][j-1];
    }
  }

  int n, m;
  while (cin >> n >> m && !(n == 0 && m == 0)) {
    cout << n << " things taken " << m << " at a time is " << c[n][m] << " exactly." << endl;
  }

  return 0;
}
