#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;
static const int INF = 10000000;

struct planet { int id, x, y, z; };

int inline sqr(int x) { return x * x; }

int bfs(const vector<vector<int> >& g, int start, vector<int>& prev)
{
  const int N = g.size();
  prev.assign(N, -1);
  queue<int> q;
  q.push(start);
  vector<int> dist(N, INF);
  dist[start] = 0;
  int maxd = 0;
  int idx = 0;
  while (!q.empty()) {
    const int n = q.front();
    q.pop();
    const int d = dist[n];
    if (maxd < d) {
      maxd = dist[n];
      idx = n;
    }
    for (vector<int>::const_iterator it = g[n].begin(); it != g[n].end(); ++it) {
      if (d+1 < dist[*it]) {
        prev[*it] = n;
        dist[*it] = d+1;
        q.push(*it);
      }
    }
  }
  return idx;
}

int main()
{
  int N;
  while (cin >> N && N != 0) {
    vector<planet> ps;
    vector<vector<int> > g(N);
    for (int i = 0; i < N; i++) {
      planet p;
      cin >> p.id >> p.x >> p.y >> p.z;
      ps.push_back(p);
      int m = INF;
      int idx = -1;
      for (int j = 0; j < i; j++) {
        const int d = sqr(ps[j].x - p.x) + sqr(ps[j].y - p.y) + sqr(ps[j].z - p.z);
        if (d < m) {
          m = d;
          idx = j;
        }
      }
      if (idx != -1) {
        g[i].push_back(idx);
        g[idx].push_back(i);
      }
    }

    vector<int> prev;
    const int u = bfs(g, 0, prev);
    const int v = bfs(g, u, prev);
    vector<int> path;
    for (int x = v; prev[x] != -1; x = prev[x]) {
      path.push_back(x);
    }
    path.push_back(u);
    const int M = path.size();
    if (M % 2 == 0) {
      int a = ps[path[M/2-1]].id;
      int b = ps[path[M/2]].id;
      if (a > b) {
        swap(a, b);
      }
      cout << a << ' ' << b << endl;
    } else {
      cout << ps[path[M/2]].id << endl;
    }
  }
  return 0;
}
