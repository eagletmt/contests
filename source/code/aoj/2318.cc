#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>
using namespace std;
static const int INF = 10000000;

pair<vector<int>, bool>
bellman_ford(const vector<vector<vector<int> > >& rules, const vector<int>& seed)
{
  const int N = seed.size();
  vector<int> dist(N, INF);
  for (int i = 0; i < N; i++) {
    if (seed[i]) {
      dist[i] = 1;
    }
  }

  for (int i = 0; i < N; i++) {
    for (int u = 0; u < N; u++) {
      for (vector<vector<int> >::const_iterator it = rules[u].begin(); it != rules[u].end(); ++it) {
        vector<int> v;
        for (vector<int>::const_iterator jt = it->begin(); jt != it->end(); ++jt) {
          v.push_back(dist[*jt]);
        }
        sort(v.begin(), v.end(), greater<int>());
        int d = 0;
        for (vector<int>::const_iterator jt = v.begin(); jt != v.end(); ++jt) {
          d = max(d, int(*jt + (jt - v.begin())));
        }
        dist[u] = min(dist[u], d);
      }
    }
  }

  for (int u = 0; u < N; u++) {
    for (vector<vector<int> >::const_iterator it = rules[u].begin(); it != rules[u].end(); ++it) {
      vector<int> v;
      for (vector<int>::const_iterator jt = it->begin(); jt != it->end(); ++jt) {
        v.push_back(dist[*jt]);
      }
      sort(v.begin(), v.end(), greater<int>());
      int d = 0;
      for (vector<int>::const_iterator jt = v.begin(); jt != v.end(); ++jt) {
        d = max(d, int(*jt + (jt - v.begin())));
      }
      if (d < dist[u]) {
        return make_pair(dist, false);
      }
    }
  }
  return make_pair(dist, true);
}

int main()
{
  int N, E, T;
  cin >> N >> E >> T;
  --T;
  vector<int> seed(N);
  for (int i = 0; i < N; i++) {
    cin >> seed[i];
  }
  vector<vector<vector<int> > > rules(N);
  for (int i = 0; i < E; i++) {
    int g, c;
    cin >> g >> c;
    --g;
    vector<int> r(c);
    for (int j = 0; j < c; j++) {
      cin >> r[j];
      --r[j];
    }
    rules[g].push_back(r);
  }

  const pair<vector<int>, bool> r = bellman_ford(rules, seed);
  if (r.second && r.first[T] < INF) {
    cout << r.first[T] << endl;
  } else {
    cout << "-1" << endl;
  }
  return 0;
}
