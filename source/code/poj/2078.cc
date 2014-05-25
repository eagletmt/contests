#include <iostream>
#include <cmath>
#include <vector>
#include <limits>
#include <algorithm>
using namespace std;

int work(const vector<vector<int> >& a)
{
  const int N = a.size();
  int m = 0;
  for (int j = 0; j < N; j++) {
    int s = 0;
    for (int i = 0; i < N; i++) {
      s += a[i][j];
    }
    m = max(m, s);
  }
  return m;
}

int solve(vector<vector<int> >& a)
{
  const int N = a.size();
  const int EN = static_cast<int>(pow(static_cast<double>(N), static_cast<double>(N)));
  vector<int> steps(N, 0);
  int ans = numeric_limits<int>::max();
  ans = min(ans, work(a));
  for (int s = 1; s < EN; s++) {
    rotate(a[0].begin(), a[0].begin()+1, a[0].end());
    ++steps[0];
    int i = 0;
    while (steps[i] == N) {
      steps[i] = 0;
      ++i;
      ++steps[i];
      rotate(a[i].begin(), a[i].begin()+1, a[i].end());
    }
    ans = min(ans, work(a));
  }
  return ans;
}

int main()
{
  int n;
  while (cin >> n && n != -1) {
    vector<vector<int> > a(n, vector<int>(n));
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < n; j++) {
        cin >> a[i][j];
      }
    }
    cout << solve(a) << endl;
  }
  return 0;
}
