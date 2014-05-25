#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main()
{
  int T;
  cin >> T;
  while (T-- > 0) {
    int N, M;
    cin >> N >> M;
    vector<vector<int> > lt(N, vector<int>(N, 0)), gt(N, vector<int>(N, 0));
    for (int i = 0; i < M; i++) {
      int u, v;
      cin >> u >> v;
      u--;  v--;
      lt[u][v] = 1;
      gt[v][u] = 1;
    }

    for (int k = 0; k < N; k++) {
      for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
          if (lt[i][k] && lt[k][j]) {
            lt[i][j] = 1;
          }
        }
      }
    }
    for (int k = 0; k < N; k++) {
      for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
          if (gt[i][k] && gt[k][j]) {
            gt[i][j] = 1;
          }
        }
      }
    }

    int ans = 0;
    for (int i = 0; i < N; i++) {
      if (count(lt[i].begin(), lt[i].end(), 1) > N/2
          || count(gt[i].begin(), gt[i].end(), 1) > N/2) {
        ++ans;
      }
    }
    cout << ans << endl;
  }
  return 0;
}
