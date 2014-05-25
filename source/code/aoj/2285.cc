#include <iostream>
#include <algorithm>
using namespace std;

int main()
{
  int L, N, M, X;
  while (cin >> L >> N >> M >> X && L != 0) {
    static pair<int,int> sec[100];
    for (int i = 0; i < N; i++) {
      string s;
      cin >> s >> sec[i].first >> sec[i].second;
    }
    static pair<int,int> sta[100];
    for (int i = 0; i < M; i++) {
      string s;
      cin >> s >> sta[i].first >> sta[i].second;
    }
    sort(sta, sta+M);

    int ans = 0;
    for (int i = 0; i < N; i++) {
      for (int j = i; j < N; j++) {
        int E = L - sec[i].first;
        int S = sec[i].second;
        if (i != j) {
          E -= sec[j].first;
          S += sec[j].second;
        }
        if (E < X) {
          continue;
        }
        static int dp[1000];
        static int cnt[1000];
        fill_n(dp, E+1, 0);
        fill_n(cnt, E+1, 0);
        int a = 0;
        for (int k = 0; k < M; k++) {
          for (int l = E - sta[k].first; l >= 0; l--) {
            if (dp[l+sta[k].first] < dp[l]+sta[k].second) {
              dp[l+sta[k].first] = dp[l]+sta[k].second;
              cnt[l+sta[k].first] = cnt[l]+1;
              if (cnt[l+sta[k].first] >= X) {
                a = max(a, dp[l+sta[k].first]);
              }
            }
          }
        }
        if (a != 0) {
          ans = max(ans, a+S);
        }
      }
    }
    cout << ans << endl;
  }
  return 0;
}
