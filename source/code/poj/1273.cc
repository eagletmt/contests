#include <iostream>
#include <vector>
#include <queue>
#include <limits>
using namespace std;

template <typename T>
T edmonds_karp(int N, vector<vector<T> > capacity, int source, int sink)
{
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
        if (parent[u] < 0 && capacity[v][u] > 0) {
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
      aug = min(aug, capacity[u][v]);
    }
    max_flow += aug;
    for (int v = sink; v != source; v = parent[v]) {
      const int u = parent[v];
      flow[u][v] += aug;
      flow[v][u] -= aug;
      capacity[u][v] -= aug;
      capacity[v][u] += aug;
    }
  }

  return max_flow;
}

int main()
{
  int N, M;
  while (cin >> N >> M) {
    vector<vector<long long> > cap(M, vector<long long>(M, 0));

    for (int i = 0; i < N; i++) {
      int s, e, c;
      cin >> s >> e >> c;
      cap[s-1][e-1] += c;
    }
    cout << edmonds_karp(M, cap, 0, M-1) << endl;
  }
  return 0;
}
