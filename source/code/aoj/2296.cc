#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
using namespace std;

struct town
{
  int x, y;
  vector<pair<int,int> > items;
};

inline int manhattan(const pair<int,int>& p, const pair<int,int>& q)
{
  return abs(p.first - q.first) + abs(p.second - q.second);
}

int main()
{
  int N, M, W, T;
  cin >> N >> M >> W >> T;
  map<string, int> weight, market_price;
  for (int i = 0; i < M; i++) {
    string s;
    int v, p;
    cin >> s >> v >> p;
    weight.insert(make_pair(s, v));
    market_price.insert(make_pair(s, p));
  }

  vector<town> towns;
  for (int i = 0; i < N; i++) {
    town t;
    int L;
    cin >> L >> t.x >> t.y;
    for (int j = 0; j < L; j++) {
      string r;
      int q;
      cin >> r >> q;
      t.items.push_back(make_pair(weight[r], market_price[r] - q));
    }
    towns.push_back(t);
  }

  vector<pair<int,long long> > routes;
  for (int s = 1; s < (1<<N); s++) {
    vector<pair<int,int> > posses, items;
    for (int i = 0; i < N; i++) {
      if (s & (1<<i)) {
        posses.push_back(make_pair(towns[i].x, towns[i].y));
        for (vector<pair<int,int> >::const_iterator it = towns[i].items.begin(); it != towns[i].items.end(); ++it) {
          items.push_back(*it);
        }
      }
    }

    // minimum time (tsp)
    int t = 10000000;
    sort(posses.begin(), posses.end());
    do {
      int d = 0;
      d += manhattan(make_pair(0, 0), posses.front());
      for (vector<pair<int,int> >::const_iterator it = posses.begin(); it+1 != posses.end(); ++it) {
        d += manhattan(*it, *(it+1));
      }
      d += manhattan(posses.back(), make_pair(0, 0));
      t = min(t, d);
    } while (next_permutation(posses.begin(), posses.end()));

    // maximum profit (knapsack)
    vector<long long> dp(W+1, 0LL);
    long long prof = 0LL;
    for (vector<pair<int,int> >::const_iterator it = items.begin(); it != items.end(); ++it) {
      for (int i = 0; i + it->first <= W; i++) {
        dp[i + it->first] = max(dp[i + it->first], dp[i] + it->second);
        prof = max(prof, dp[i + it->first]);
      }
    }
    routes.push_back(make_pair(t, prof));
  }

  // maximum profit (knapsack)
  vector<long long> dp(T+1, 0LL);
  long long ans = 0LL;
  for (vector<pair<int,long long> >::const_iterator it = routes.begin(); it != routes.end(); ++it) {
    for (int i = 0; i + it->first <= T; i++) {
      dp[i + it->first] = max(dp[i + it->first], dp[i] + it->second);
      ans = max(ans, dp[i + it->first]);
    }
  }
  cout << ans << endl;
  return 0;
}
