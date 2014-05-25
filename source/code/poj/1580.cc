#include <iostream>
#include <vector>
using namespace std;

int gcd(int a, int b)
{
  if (a < b) {
    swap(a, b);
  }
  int r;
  while ((r = a % b) != 0) {
    a = b;
    b = r;
  }
  return b;
}

int main()
{
  string s;
  while (cin >> s && s != "-1") {
    string t;
    cin >> t;

    const int N = s.size(), M = t.size();
    int ans = 0;
    for (int i = 0; i < N; i++) {
      int c = 0;
      for (int j = 0; j < M && i+j < N; j++) {
        if (s[i+j] == t[j]) {
          ++c;
        }
      }
      ans = max(ans, 2*c);
    }
    for (int j = 0; j < M; j++) {
      int c = 0;
      for (int i = 0; i < N && j+i < M; i++) {
        if (s[i] == t[j+i]) {
          ++c;
        }
      }
      ans = max(ans, 2*c);
    }

    int d = N + M;
    cout << "appx(" << s << "," << t << ") = ";
    if (ans == 0) {
      cout << "0";
    } else if (ans == d) {
      cout << "1";
    } else {
      int g = gcd(ans, d);
      ans /= g; d /= g;
      cout << ans << "/" << d;
    }
    cout << endl;
  }
  return 0;
}
