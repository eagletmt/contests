#include <iostream>
using namespace std;

int dp[30];
int f(int w)
{
  int &a = dp[w];
  if (a != 0) {
    return a;
  } else {
    a += f(w-1);
    a += 4*f(w-2);
    for (int i = 3; i <= w; i++) {
      a += (i & 1 ? 2 : 3) * f(w-i);
    }
    return a;
  }
}

int main()
{
  dp[0] = dp[1] = 1;
  int T;
  cin >> T;
  for (int Ti = 1; Ti <= T; Ti++) {
    int w;
    cin >> w;
    cout << Ti << ' ' << f(w) << endl;
  }
  return 0;
}
