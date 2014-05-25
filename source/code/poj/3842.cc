#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main()
{
  static const int N = 10000000;
  static bool sieve[N];
  sieve[0] = sieve[1] = true;
  for (int i = 2; i < N; i++) {
    if (!sieve[i]) {
      for (int j = i+i; j < N; j += i) {
        sieve[j] = true;
      }
    }
  }

  int C;
  cin >> C;
  while (C-- > 0) {
    string s;
    cin >> s;
    const int M = s.size();
    vector<int> v;
    for (int u = 1; u < (1<<M); u++) {
      string t;
      for (int i = 0; i < M; i++) {
        if (u & (1<<i)) {
          t += s[i];
        }
      }
      sort(t.begin(), t.end());
      do {
        int n = 0;
        for (string::const_iterator it(t.begin()); it != t.end(); ++it) {
          n = 10*n + *it-'0';
        }
        if (!sieve[n]) {
          v.push_back(n);
        }
      } while (next_permutation(t.begin(), t.end()));
    }
    sort(v.begin(), v.end());
    const vector<int>::iterator it = unique(v.begin(), v.end());
    cout << distance(v.begin(), it) << endl;
  }
  return 0;
}
