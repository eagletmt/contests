#include <iostream>
#include <vector>
#include <queue>
#include <limits>
using namespace std;

template <typename T>
pair<T, vector<vector<T> > >
edmonds_karp(const vector<vector<T> >& capacity, int source, int sink)/*{{{*/
{
  const int N = capacity.size();
  vector<vector<T> > flow(N, vector<T>(N, 0));
  T max_flow = 0;

  while (true) {
    vector<int> parent(N, -1);
    queue<int> q;
    q.push(source);

    while (!q.empty() && parent[sink] < 0) {
      const int v = q.front();
      q.pop();

      for (int u = 0; u < N; u++) {
        if (parent[u] < 0 && capacity[v][u] - flow[v][u] > 0) {
          parent[u] = v;
          if (u == sink) {
            break;
          }
          q.push(u);
        }
      }
    }

    if (parent[sink] < 0) {
      break;
    }

    T aug = numeric_limits<T>::max();
    for (int v = sink; v != source; v = parent[v]) {
      const int u = parent[v];
      aug = min(aug, capacity[u][v] - flow[u][v]);
    }
    max_flow += aug;
    for (int v = sink; v != source; v = parent[v]) {
      const int u = parent[v];
      flow[u][v] += aug;
      flow[v][u] -= aug;
    }
  }

  return make_pair(max_flow, flow);
}/*}}}*/

int main()
{
  int N, M;
  cin >> N >> M;
  vector<vector<int> > capacity(N, vector<int>(N, 0));
  vector<pair<int,int> > edges;
  for (int i = 0; i < M; i++) {
    int u, v;
    cin >> u >> v;
    --u;  --v;
    ++capacity[u][v];
    ++capacity[v][u];
    edges.push_back(make_pair(u, v));
  }
  int S, T;
  cin >> S >> T;
  --S;  --T;

  const pair<int, vector<vector<int> > > r = edmonds_karp(capacity, S, T);
  cout << r.first << endl;
  vector<int> ans;
  const vector<vector<int> >& flow = r.second;
  for (int i = 0; i < M; i++) {
    if (flow[edges[i].second][edges[i].first] > 0) {
      ans.push_back(i);
    }
  }
  cout << ans.size() << endl;
  for (vector<int>::const_iterator it = ans.begin(); it != ans.end(); ++it) {
    cout << *it+1 << endl;
  }

  return 0;
}
