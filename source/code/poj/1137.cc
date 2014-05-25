#include <iostream>
#include <sstream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

int main()
{
  int R, D, S;
  for (int Ti = 1; cin >> R >> D >> S && R != 0; Ti++) {
    vector<vector<int> > g(R);
    for (int i = 0; i < D; i++) {
      int u, v;
      cin >> u >> v;
      --u;  --v;
      g[u].push_back(v);
      g[v].push_back(u);
    }
    vector<vector<int> > switches(R);
    for (int i = 0; i < S; i++) {
      int u, v;
      cin >> u >> v;
      --u;  --v;
      if (u != v) {
        switches[u].push_back(v);
      }
    }
    for (int i = 0; i < R; i++) {
      sort(switches[i].begin(), switches[i].end());
    }

    queue<pair<int,int> > q;
    q.push(make_pair(0, 1));
    vector<vector<int> > dist(R, vector<int>(1<<R, 1000000));
    vector<vector<pair<bool,int> > > prev(R, vector<pair<bool,int> >(1<<R));
    dist[0][1] = 0;
    cout << "Villa #" << Ti << endl;
    while (!q.empty()) {
      int n = q.front().first;
      int s = q.front().second;
      q.pop();
      const int d = dist[n][s];
      if (n == R-1 && s == (1<<(R-1))) {
        cout << "The problem can be solved in " << d << " steps:" << endl;
        vector<string> msg;
        for (int i = 0; i < d; i++) {
          ostringstream oss;
          const int j = prev[n][s].second;
          if (prev[n][s].first) {
            // switch
            oss << "- Switch " << (s & (1<<j) ? "on" : "off") << " light in room " << j+1 << ".";
            s ^= (1<<j);
          } else {
            // move
            oss << "- Move to room " << n+1 << ".";
            n = j;
          }
          msg.push_back(oss.str());
        }
        for (vector<string>::reverse_iterator it = msg.rbegin(); it != msg.rend(); ++it) {
          cout << *it << endl;
        }
        goto NEXT;
      }
      // goto next room
      for (vector<int>::const_iterator it(g[n].begin()); it != g[n].end(); ++it) {
        if (s & (1<<*it) && d+1 < dist[*it][s]) {
          dist[*it][s] = d+1;
          prev[*it][s].first = false;
          prev[*it][s].second = n;
          q.push(make_pair(*it, s));
        }
      }
      // turn switch
      for (vector<int>::const_iterator it(switches[n].begin()); it != switches[n].end(); ++it) {
        const int t = s ^ (1<<*it);
        if (d+1 < dist[n][t]) {
          dist[n][t] = d+1;
          prev[n][t].first = true;
          prev[n][t].second = *it;
          q.push(make_pair(n, t));
        }
      }
    }
    cout << "The problem cannot be solved." << endl;
NEXT:
    cout << endl;
  }
  return 0;
}
