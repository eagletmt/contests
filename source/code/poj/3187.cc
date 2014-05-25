#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int comb[11][11];

int sum(const vector<int>& a)
{
  const int N = a.size();
  int s = 0;
  for (int i = 0; i < N; i++) {
    s += a[i] * comb[N-1][i];
  }
  return s;
}

int main()
{
  for (int i = 0; i <= 10; i++) {
    comb[i][0] = 1;
    comb[i][i] = 1;
  }
  for (int n = 1; n <= 10; n++) {
    for (int k = 1; k < n; k++) {
      comb[n][k] = comb[n-1][k] + comb[n-1][k-1];
    }
  }

  int N, S;
  cin >> N >> S;
  vector<int> a(N);
  for (int i = 0; i < N; i++) {
    a[i] = i+1;
  }

  do {
    if (sum(a) == S) {
      for (int i = 0; i < N; i++) {
        if (i != 0) {
          cout << ' ';
        }
        cout << a[i];
      }
      cout << endl;
      break;
    }
  } while (next_permutation(a.begin(), a.end()));
  return 0;
}
