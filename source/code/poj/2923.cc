#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
static const int INF = 10000;

int f(vector<int>& v, int C)
{
  int c = 0;
  while (!v.empty()) {
    if (v[0] > C) {
      return INF;
    }
    int r = C;
    for (vector<int>::iterator it = v.begin(); it != v.end();) {
      if (*it <= r) {
        r -= *it;
        it = v.erase(it);
      } else {
        ++it;
      }
    }
    ++c;
  }
  return c;
}

int main()
{
  int T;
  cin >> T;
  for (int Ti = 1; Ti <= T; Ti++) {
    int N, C1, C2;
    cin >> N >> C1 >> C2;
    vector<int> v(N);
    for (int i = 0; i < N; i++) {
      cin >> v[i];
    }
    sort(v.rbegin(), v.rend());

    int ans = INF;
    for (unsigned s = 0; s < (1U<<N); s++) {
      vector<int> w[2];
      for (int i = 0; i < N; i++) {
        w[!(s & (1<<i))].push_back(v[i]);
      }
      ans = min(ans, max(f(w[0], C1), f(w[1], C2)));
    }
    cout << "Scenario #" << Ti << ":" << endl;
    cout << ans << endl << endl;
  }
  return 0;
}
