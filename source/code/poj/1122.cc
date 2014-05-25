#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

int main()
{
  static const int INF = 10000000;
  ios::sync_with_stdio(false);
  int N;
  cin >> N;
  vector<vector<int> > m(N, vector<int>(N));
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < N; j++) {
      cin >> m[j][i];
    }
  }
  int dest;
  cin >> dest;
  --dest;
  vector<int> closest;
  for (int n; cin >> n;) {
    --n;
    closest.push_back(n);
  }

  vector<int> dist(N, INF);
  vector<int> prev(N, -1);
  dist[dest] = 0;
  priority_queue<pair<int,int> > q;
  q.push(make_pair(0, dest));
  while (!q.empty()) {
    const int cost = -q.top().first;
    const int n = q.top().second;
    q.pop();
    if (dist[n] < cost) {
      continue;
    }
    for (int i = 0; i < N; i++) {
      if (m[n][i] == -1) {
        continue;
      }
      const int cc = cost + m[n][i];
      if (cc < dist[i]) {
        dist[i] = cc;
        prev[i] = n;
        q.push(make_pair(-cc, i));
      }
    }
  }

  cout << "Org\tDest\tTime\tPath" << endl;
  vector<pair<int,int> > output;
  for (vector<int>::const_iterator it = closest.begin(); it != closest.end(); ++it) {
    output.push_back(make_pair(dist[*it], *it));
  }
  sort(output.begin(), output.end());
  for (vector<pair<int,int> >::const_iterator it = output.begin(); it != output.end(); ++it) {
    cout << it->second+1 << "\t" << dest+1 << "\t" << it->first;
    for (int n = it->second; n != -1; n = prev[n]) {
      cout << "\t" << n+1;
    }
    cout << endl;
  }
  return 0;
}
