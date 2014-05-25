#include <iostream>
#include <vector>
using namespace std;

struct edge
{
  int u, v, c;
  edge(int x, int y, int z) : u(x), v(y), c(z) {}
};

int main()
{
  int N, ML, MD;
  cin >> N >> ML >> MD;
  vector<edge> es;
  for (int i = 1; i < N; i++) {
    es.push_back(edge(i, i-1, 0));
  }
  for (int i = 0; i < ML; i++) {
    int u, v, c;
    cin >> u >> v >> c;
    --u;  --v;
    es.push_back(edge(u, v, c));
  }
  for (int i = 0; i < MD; i++) {
    int u, v, c;
    cin >> u >> v >> c;
    --u;  --v;
    es.push_back(edge(v, u, -c));
  }

  static const long long INF = 1LL<<50;
  vector<long long> dist(N, INF);
  dist[0] = 0;
  for (int i = 0; i < N; i++) {
    for (vector<edge>::const_iterator it = es.begin(); it != es.end(); ++it) {
      dist[it->v] = min(dist[it->v], dist[it->u] + it->c);
    }
  }
  for (vector<edge>::const_iterator it = es.begin(); it != es.end(); ++it) {
    if (dist[it->u] + it->c < dist[it->v]) {
      cout << "-1" << endl;
      return 0;
    }
  }
  if (dist[N-1] == INF) {
    cout << "-2" << endl;
  } else {
    cout << dist[N-1] << endl;
  }
  return 0;
}
