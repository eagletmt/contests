#include <iostream>
#include <vector>
#include <map>
#include <queue>
using namespace std;

int numbering(map<string,int>& m, const string& s)
{
  const map<string,int>::const_iterator it = m.find(s);
  if (it == m.end()) {
    const int n = m.size();
    m.insert(make_pair(s, n));
    return n;
  } else {
    return it->second;
  }
}

int dijkstra(const vector<vector<pair<int,int> > >& g, int start, int goal)
{
  priority_queue<pair<int,int> > q;
  vector<int> dist(g.size(), 10000000);
  q.push(make_pair(0, start));
  dist[start] = 0;
  while (!q.empty()) {
    const int c = -q.top().first;
    const int n = q.top().second;
    q.pop();
    if (n == goal) {
      return c;
    }
    if (dist[n] < c) {
      continue;
    }
    for (vector<pair<int,int> >::const_iterator it = g[n].begin(); it != g[n].end(); ++it) {
      const int cc = c + it->second;
      if (cc < dist[it->first]) {
        dist[it->first] = cc;
        q.push(make_pair(-cc, it->first));
      }
    }
  }
  throw "fail";
}

int main()
{
  int N, M;
  while (cin >> N >> M && N != 0) {
    map<string,int> m;
    string s, p, q;
    cin >> s >> p >> q;
    const int ss = numbering(m, s);
    const int pp = numbering(m, p);
    const int qq = numbering(m, q);
    vector<vector<pair<int,int> > > g(N);
    for (int i = 0; i < M; i++) {
      string u, v;
      int d, t;
      cin >> u >> v >> d >> t;
      const int c = d/40+t;
      const int uu = numbering(m, u);
      const int vv = numbering(m, v);
      g[uu].push_back(make_pair(vv, c));
      g[vv].push_back(make_pair(uu, c));
    }
    cout << dijkstra(g, ss, pp) + dijkstra(g, pp, qq) << endl;
  }
  return 0;
}
