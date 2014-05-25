#include <iostream>
#include <sstream>
#include <vector>
#include <numeric>
using namespace std;

int main()
{
  for (string s; getline(cin, s) && s != "ENDOFINPUT";) {
    int N;
    {
      istringstream iss(s);
      iss >> s >> N;
    }
    vector<vector<int> > v(N);
    for (int i = 0; i < N; i++) {
      getline(cin, s);
      istringstream iss(s);
      for (int x; iss >> x;) {
        v[i].push_back(x);
      }
    }
    int T;
    {
      getline(cin, s);
      istringstream iss(s);
      iss >> T;
    }
    getline(cin, s);

    int ans = 10000000;
    for (int i = 0; i < N; i++) {
      int t = T % accumulate(v[i].begin(), v[i].end(), 0);
      if (t == 0) {
        ans = 0;
        break;
      }
      int acc = 0;
      for (vector<int>::const_iterator it = v[i].begin(); it != v[i].end(); ++it) {
        acc += *it;
        if (acc >= t) {
          ans = min(ans, acc-t);
          break;
        }
      }
    }
    cout << ans << endl;
  }
  return 0;
}
