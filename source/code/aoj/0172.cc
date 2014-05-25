#include <iostream>
#include <sstream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

int main()
{
  int N, M;
  while (cin >> N >> M && N != 0) {
    vector<vector<int> > g(N);
    for (int i = 0; i < M; i++) {
      int s, t;
      cin >> s >> t;
      --s;  --t;
      g[s].push_back(t);
      g[t].push_back(s);
    }
    unsigned init = 0;
    for (int i = 0; i < N; i++) {
      int x;
      cin >> x;
      init |= (x<<i);
    }
    vector<vector<int> > switches(N);
    for (int i = 0; i < N; i++) {
      int k;
      cin >> k;
      for (int j = 0; j < k; j++) {
        int r;
        cin >> r;
        --r;
        switches[i].push_back(r);
      }
      sort(switches[i].begin(), switches[i].end());
    }

    queue<pair<int,unsigned> > q;
    static const int INF = 10000000;
    vector<vector<int> > dist(N, vector<int>(1<<N, INF));
    q.push(make_pair(0, init));
    dist[0][init] = 0;
    vector<vector<pair<int,unsigned> > > prev(N, vector<pair<int,unsigned> >(1<<N));
    while (!q.empty() && dist[N-1][1<<(N-1)] == INF) {
      int n = q.front().first;
      unsigned s = q.front().second;
      q.pop();

      for (vector<int>::const_iterator it = g[n].begin(); it != g[n].end(); ++it) {
        if (s & (1<<*it) && dist[n][s] + 1 < dist[*it][s]) {
          dist[*it][s] = dist[n][s] + 1;
          prev[*it][s] = make_pair(n, s);
          q.push(make_pair(*it, s));
        }
      }

      for (vector<int>::const_iterator it = switches[n].begin(); it != switches[n].end(); ++it) {
        if (*it != n) {
          unsigned t = s ^ (1<<*it);
          if (dist[n][s] + 1 < dist[n][t]) {
            dist[n][t] = dist[n][s] + 1;
            prev[n][t] = make_pair(n, s);
            q.push(make_pair(n, t));
          }
        }
      }
    }
    if (dist[N-1][1<<(N-1)] != INF) {
      cout << "You can go home in " << dist[N-1][1<<(N-1)] << " steps." << endl;
      int n = N-1;
      unsigned s = 1<<(N-1);
      vector<string> logs;
      for (int i = 0; i < dist[N-1][1<<(N-1)]; i++) {
        const int m = prev[n][s].first;
        const unsigned t = prev[n][s].second;
        ostringstream oss;
        if (n == m) {
          const unsigned u = s ^ t;
          int r;
          for (r = 0; r < N; r++) {
            if (u & (1<<r)) {
              break;
            }
          }
          oss << "Switch " << (s & (1<<r) ? "on" : "off") << " room " << r+1 << ".";
        } else {
          oss << "Move to room " << n+1 << ".";
        }
        logs.push_back(oss.str());
        n = m;
        s = t;
      }
      for (vector<string>::const_reverse_iterator it = logs.rbegin(); it != logs.rend(); ++it) {
        cout << *it << endl;
      }
    } else if (*min_element(dist[N-1].begin(), dist[N-1].end()) == INF) {
      cout << "Help me!" << endl;
    } else {
      cout << "You can not switch off all lights." << endl;
    }
  }
  return 0;
}
