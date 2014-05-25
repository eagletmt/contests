#include <iostream>
#include <vector>
#include <limits>
#include <algorithm>
using namespace std;

template<typename T, typename F> 
vector<vector<T> > floyd(const vector<vector<pair<int,T> > >& g, const F& f)
{
  const int N = g.size();
  vector<vector<T> > dist(N, vector<T>(N, numeric_limits<T>::max()/N));
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < g[i].size(); j++) {
      const int to = g[i][j].first;
      dist[i][to] = g[i][j].second;
    }
  }

  for (int k = 0; k < N; k++) {
    for (int i = 0; i < N; i++) {
      for (int j = 0; j < N; j++) {
        dist[i][j] = min(dist[i][j], f(dist[i][k], dist[k][j]));
      }
    }
  }
  return dist;
}

int main()
{
  int N;
  while (cin >> N && N != 0) {
    vector<vector<pair<int,int> > > g(N);
    for (int i = 0; i < N; i++) {
      int n;
      cin >> n;
      for (int j = 0; j < n; j++) {
        int s, c;
        cin >> s >> c;
        g[i].push_back(make_pair(s-1, c));
      }
    }

    const vector<vector<int> > dist = floyd(g, plus<int>());
    int ans_start, ans_dist = numeric_limits<int>::max();
    for (int i = 0; i < N; i++) {
      int m = 0;
      for (int j = 0; j < N; j++) {
        if (i != j) {
          m = max(m, dist[i][j]);
        }
      }
      if (ans_dist > m) {
        ans_start = i+1;
        ans_dist = m;
      }
    }
    if (ans_dist == numeric_limits<int>::max()) {
      cout << "disjoint" << endl;
    } else {
      cout << ans_start << ' ' << ans_dist << endl;
    }
  }
}
