#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

bool ok(const vector<int>& v, int M, int l)
{
  int prev = 0;
  int c = 0;
  for (vector<int>::const_iterator it = v.begin(); it != v.end(); ++it) {
    const int d = *it - prev;
    if (d < l) {
      // remove
      ++c;
    } else {
      prev = *it;
    }
  }
  return c <= M;
}

int main()
{
  int L, N, M;
  cin >> L >> N >> M;
  vector<int> v(N);
  for (int i = 0; i < N; i++) {
    cin >> v[i];
  }

  sort(v.begin(), v.end());
  int lo = 0, hi = L;
  while (lo < hi) {
    const int mid = (lo + hi + 1)/2;
    if (ok(v, M, mid)) {
      lo = mid;
    } else {
      hi = mid-1;
    }
  }
  cout << lo << endl;
  return 0;
}
