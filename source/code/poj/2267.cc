#include <iostream>
#include <vector>
#include <map>
#include <queue>
using namespace std;

struct edge { int to, dep, time; };

struct state
{
  int idx, cost, hour;
  state(int i, int c, int h) : idx(i), cost(c), hour(h) {}
  bool operator<(const state& that) const
  {
    if (cost != that.cost) {
      return cost > that.cost;
    } else {
      return hour > that.hour;
    }
  }
};

int main()
{
  int T;
  cin >> T;
  for (int Ti = 1; Ti <= T; Ti++) {
    int M;
    cin >> M;
    map<string,int> dict;
    vector<vector<edge> > g;
    for (int i = 0; i < M; i++) {
      string from, to;
      edge e;
      cin >> from >> to >> e.dep >> e.time;
      e.dep %= 24;
      if (e.dep >= 18) {
        e.dep -= 18;
      } else {
        e.dep = (e.dep + 6);
      }

      if (e.dep + e.time > 12) {
        continue;
      }
      if (!dict.count(from)) {
        dict.insert(make_pair(from, dict.size()));
        g.push_back(vector<edge>());
      }
      if (!dict.count(to)) {
        dict.insert(make_pair(to, dict.size()));
        g.push_back(vector<edge>());
      }
      e.to = dict[to];
      g[dict[from]].push_back(e);
    }
    const int N = g.size();

    string from, to;
    cin >> from >> to;
    cout << "Test Case " << Ti << "." << endl;
    if (!dict.count(from) || !dict.count(to)) {
      cout << "There is no route Vladimir can take." << endl;
      continue;
    }
    const int start = dict[from], goal = dict[to];
    static const int INF = 10000000;
    vector<vector<int> > dist(N, vector<int>(24, INF));
    priority_queue<state> q;
    q.push(state(start, 0, 0));
    dist[start][0] = 0;
    int ans = INF;
    while (!q.empty()) {
      const int cost = q.top().cost;
      const int n = q.top().idx;
      const int h = q.top().hour;
      q.pop();
      if (n == goal) {
        ans = min(ans, cost);
        continue;
      }
      if (cost < dist[n][h]) {
        continue;
      }

      for (vector<edge>::const_iterator it = g[n].begin(); it != g[n].end(); ++it) {
        if (h <= it->dep) {
          const int nn = it->to;
          const int hh = it->dep + it->time;
          if (cost < dist[nn][hh]) {
            dist[nn][hh] = cost;
            q.push(state(nn, cost, hh));
          }
        }
      }
      if (cost+1 < dist[n][0]) {
        dist[n][0] = cost+1;
        q.push(state(n, cost+1, 0));
      }
    }
    if (ans == INF) {
      cout << "There is no route Vladimir can take." << endl;
    } else {
      cout << "Vladimir needs " << ans << " litre(s) of blood." << endl;
    }
NEXT:
    ;
  }
  return 0;
}
