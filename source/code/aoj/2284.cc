#include <iostream>
#include <sstream>
#include <vector>
#include <algorithm>
using namespace std;

int main()
{
  int W, H;
  while (cin >> W >> H && W != 0) {
    static vector<pair<int,int> > ps[3000];
    for (int i = 0; i < 3000; i++) {
      ps[i].clear();
    }
    pair<int,int> g;
    int m = 0;
    for (int i = 0; i < H; i++) {
      for (int j = 0; j < W; j++) {
        string s;
        cin >> s;
        istringstream iss(s);
        int n;
        if (s == "S") {
          ps[0].push_back(make_pair(i, j));
        } else if (s == "G") {
          g = make_pair(i, j);
        } else if (iss >> n) {
          ps[n].push_back(make_pair(i, j));
          m = max(m, n);
        }
      }
    }
    ps[++m].push_back(g);

    static int dp[3000][3000];
    for (int i = 1; i <= m; i++) {
      fill_n(dp[i], ps[i].size(), 10000000);
      for (int j = 0; j < ps[i-1].size(); j++) {
        for (int k = 0; k < ps[i].size(); k++) {
          const int l = abs(ps[i][k].first - ps[i-1][j].first) + abs(ps[i][k].second - ps[i-1][j].second);
          dp[i][k] = min(dp[i][k], dp[i-1][j] + l);
        }
      }
    }
    cout << dp[m][0] << endl;
  }
  return 0;
}
