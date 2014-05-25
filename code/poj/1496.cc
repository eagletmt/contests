#include <iostream>
using namespace std;

int comb[27][27];

int encode(const string& s)
{
  const int len = s.size();
  int r = 0;
  for (int i = 0; i < len; i++) {
    if (s[i-1] < s[i]) {
      r = r + comb[26][i+1] - comb[26-(s[i]-'a'+1)][len-i];
    } else {
      return 0;
    }
  }
  return r;
}

int main()
{
  for (int i = 0; i <= 26; i++) {
    comb[i][0] = 1;
    comb[i][i] = 1;
  }
  for (int n = 1; n <= 26; n++) {
    for (int k = 1; k < n; k++) {
      comb[n][k] = comb[n-1][k] + comb[n-1][k-1];
    }
  }

  string s;
  while (cin >> s) {
    cout << encode(s) << endl;
  }

  return 0;
}
