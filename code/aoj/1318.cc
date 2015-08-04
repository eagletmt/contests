#include <iostream>
#include <vector>
#include <map>
#include <queue>
using namespace std;

int main()
{
  int N, M, C;
  while (cin >> N >> M >> C && N != 0) {
    C *= 10;
    map<string,int> m;
    string start, goal;
    cin >> start >> goal;
    m.insert(make_pair(start, 0));
    m.insert(make_pair(goal, 1));
    vector<vector<pair<int,int> > > gg(2);
    for (int i = 0; i < N; i++) {
      string src, dst;
      int d;
      cin >> src >> dst >> d;
      int u, v;
      if (!m.count(src)) {
        u = m.size();
        m.insert(make_pair(src, u));
        gg.push_back(vector<pair<int,int> >());
      } else {
        u = m[src];
      }
      if (!m.count(dst)) {
        v = m.size();
        m.insert(make_pair(dst, v));
        gg.push_back(vector<pair<int,int> >());
      } else {
        v = m[dst];
      }
      gg[u].push_back(make_pair(v, d));
      gg[v].push_back(make_pair(u, d));
    }

    vector<int> gss, gss_map(gg.size(), -1);
    gss.push_back(0); // start
    gss.push_back(1); // goal
    gss_map[0] = 0;
    gss_map[1] = 1;
    for (int i = 0; i < M; i++) {
      string s;
      cin >> s;
      const int v = m[s];
      if (v != 0 && v != 1) {
        gss_map[v] = gss.size();
        gss.push_back(v);
      }
    }
    const int MM = gss.size();

    static const int INF = 10000000;
    vector<vector<int> > dist(MM, vector<int>(MM, INF));
    for (int i = 0; i < MM; i++) {
      priority_queue<pair<int,int> > q;
      vector<int> dp(gg.size(), INF);
      dp[gss[i]] = 0;
      q.push(make_pair(0, gss[i]));
      while (!q.empty()) {
        const int n = q.top().second;
        const int c = -q.top().first;
        q.pop();
        if (c > dp[n]) {
          continue;
        }
        for (vector<pair<int,int> >::const_iterator it = gg[n].begin(); it != gg[n].end(); ++it) {
          int k = it->first;
          const int cc = c + it->second;
          if (cc <= C && cc < dp[k]) {
            dp[k] = cc;
            if (gss_map[k] != -1) {
              dist[i][gss_map[k]] = min(dist[i][gss_map[k]], cc);
            } else {
              q.push(make_pair(-cc, k));
            }
          }
        }
      }
    }

    priority_queue<pair<int,int> > q;
    vector<int> dp(MM, INF);
    dp[0] = 0;
    q.push(make_pair(0, 0));
    while (!q.empty()) {
      const int n = q.top().second;
      const int c = -q.top().first;
      q.pop();
      if (n == 1) {
        cout << c << endl;
        goto NEXT;
      }
      for (int v = 0; v < MM; v++) {
        const int cc = c + dist[n][v];
        if (dist[n][v] != INF && cc < dp[v]) {
          dp[v] = cc;
          q.push(make_pair(-cc, v));
        }
      }
    }
    cout << "-1" << endl;
NEXT:
    ;
  }
  return 0;
}
