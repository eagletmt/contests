#include <iostream>
using namespace std;

int main()
{
  int N, T;
  cin >> N >> T;
  static int a[100];
  for (int i = 0; i < N; i++) {
    cin >> a[i];
  }

  static const int M = 10000;
  static int dp[100][2*M+1];
  dp[0][M+a[0]] = 1;
  dp[1][M+a[0]-a[1]] = -1;
  for (int i = 2; i < N; i++) {
    for (int j = -10000; j <= 10000; j++) {
      if (dp[i-1][j+M] != 0) {
        dp[i][j+a[i]+M] = 1;
        dp[i][j-a[i]+M] = -1;
      }
    }
  }

  int t = T;
  static int b[100];
  for (int i = N-1; i > 0; i--) {
    if (dp[i][t+M] == 1) {
      t -= a[i];
      b[i] = 1;
    } else if (dp[i][t+M] == -1) {
      t += a[i];
      b[i] = -1;
    }
  }

  int c = 0;
  for (int i = 1; i < N; i++) {
    if (b[i] == 1) {
      cout << i-c << endl;
      c++;
    }
  }
  for (int i = 1; i < N; i++) {
    if (b[i] == -1) {
      cout << "1" << endl;
    }
  }
  return 0;
}
