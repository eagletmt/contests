#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main()
{
  long long fact[21];
  fact[0] = 1;
  for (int i = 1; i <= 20; i++) {
    fact[i] = i * fact[i-1];
  }

  ios::sync_with_stdio(false);
  int T;
  cin >> T;
  while (T-- > 0) {
    string s;
    while (cin >> s) {
      long long ans = 0;
      const int N = s.size();
      for (int i = 0; i < N; i++) {
        vector<int> v(26, 0);
        for (int j = i; j < N; j++) {
          ++v[s[j]-'A'];
        }
        for (char c = 'A'; c < s[i]; c++) {
          long long a = fact[N-i-1];
          --v[c-'A'];
          for (int j = 0; j < 26; j++) {
            a /= fact[v[j]];
          }
          ++v[c-'A'];
          ans += a;
        }
      }
      cout << ans << endl;
    }
  }
  return 0;
}
