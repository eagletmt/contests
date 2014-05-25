#include <cstdio>
#include <vector>
#include <limits>
using namespace std;

int main()
{
  int N, M;
  scanf("%d %d", &N, &M);
  vector<vector<int> > dist(N, vector<int>(N, 1000000));
  for (int i = 0; i < M; i++) {
    int n;
    scanf("%d", &n);
    vector<int> v(n);
    for (int j = 0; j < n; j++) {
      scanf("%d", &v[j]);
      --v[j];
    }
    for (int j = 0; j < n; j++) {
      for (int k = 0; k < n; k++) {
        if (j != k) {
          dist[v[j]][v[k]] = 1;
        }
      }
    }
  }

  for (int k = 0; k < N; k++) {
    for (int i = 0; i < N; i++) {
      for (int j = 0; j < N; j++) {
        dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
      }
    }
  }

  int m = numeric_limits<int>::max();
  for (int i = 0; i < N; i++) {
    int s = 0;
    for (int j = 0; j < N; j++) {
      if (i != j) {
        s += dist[i][j];
      }
    }
    m = min(m, s);
  }
  printf("%d\n", (100*m)/(N-1));
  return 0;
}
