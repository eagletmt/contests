#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int solve(const vector<pair<int,int> >& v, int i, int j)
{
  const int N = v.size();
  const int dx = v[j].first - v[i].first;
  const int dy = v[j].second - v[i].second;
  int c = 0;
  for (int k = 0; k < N; k++) {
    if (k == i) {
      continue;
    }
    const int dxx = v[k].first - v[i].first;
    const int dyy = v[k].second - v[i].second;
    if (dx * dyy == dy * dxx) {
      ++c;
    }
  }
  return c+1;
}

int main()
{
  int N;
  cin >> N;
  vector<pair<int,int> > v(N);
  for (int i = 0; i < N; i++) {
    cin >> v[i].first >> v[i].second;
  }
  sort(v.begin(), v.end());

  int ans = 0;
  for (int i = 0; i < N; i++) {
    for (int j = i+1; j < N; j++) {
      ans = max(ans, solve(v, i, j));
    }
  }
  cout << ans << endl;
  return 0;
}
