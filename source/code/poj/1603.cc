#include <iostream>
#include <algorithm>
using namespace std;

int main()
{
  int X;
  for (int Ti = 1; cin >> X; Ti++) {
    static const int M = 20;
    int dist[M][M];
    for (int i = 0; i < M; i++) {
      fill_n(dist[i], M, 1000000);
    }

    for (int j = 0; j < X; j++) {
      int u;
      cin >> u;
      --u;
      dist[0][u] = dist[u][0] = 1;
    }
    for (int i = 1; i < M-1; i++) {
      cin >> X;
      for (int j = 0; j < X; j++) {
        int u;
        cin >> u;
        --u;
        dist[i][u] = dist[u][i] = 1;
      }
    }

    for (int k = 0; k < M; k++) {
      for (int i = 0; i < M; i++) {
        for (int j = 0; j < M; j++) {
          dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
        }
      }
    }

    int N;
    cin >> N;
    cout << "Test Set #" << Ti << endl;
    while (N-- > 0) {
      int u, v;
      cin >> u >> v;
      cout << u << " to " << v << ": " << dist[u-1][v-1] << endl;
    }
    cout << endl;
  }
  return 0;
}
