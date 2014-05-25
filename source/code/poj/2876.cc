#include <iostream>
using namespace std;

int main()
{
  string dp[13];
  dp[0] = "-";
  for (int i = 1; i <= 12; i++) {
    dp[i] = dp[i-1] + string(dp[i-1].size(), ' ') + dp[i-1];
  }
  int N;
  while (cin >> N) {
    cout << dp[N] << endl;
  }
  return 0;
}
