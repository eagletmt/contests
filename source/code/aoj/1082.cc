#include <iostream>
using namespace std;

int main()
{
  static const int N = 100000;
  static const int M = 100000007;
  static int dp1[N+1], dp2[N+1];
  dp1[1] = 1;
  dp1[2] = 2;
  dp1[3] = 4;
  dp1[4] = 8;
  dp1[5] = 16;
  for (int i = 6; i <= N; i++) {
    dp1[i] = 1;
    for (int j = 1; j <= 5; j++) {
      dp1[i] = (dp1[i] + dp1[i-j]) % M;
    }
  }
  dp2[1] = 1;
  dp2[2] = 2;
  dp2[3] = 4;
  for (int i = 4; i <= N; i++) {
    dp2[i] = 1;
    for (int j = 1; j <= 3; j++) {
      dp2[i] = (dp2[i] + dp2[i-j]) % M;
    }
  }
  string s;
  while (cin >> s && s != "#") {
    const int l = s.size();
    long long ans = 1LL;
    for (int i = 0; i < l; i++) {
      int k = i;
      while (k < l && s[k] == s[i]) {
        ++k;
      }
      if (s[i] == '8' || s[i] == '0') {
        ans = (ans * dp2[k - i]) % M;
      } else {
        ans = (ans * dp1[k - i]) % M;
      }
      --k;
      i = k;
    }
    cout << ans << endl;
  }
  return 0;
}
