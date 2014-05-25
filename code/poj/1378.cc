#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;

int main()
{
  int N, M, K;
  while (true) {
    scanf("%d %d %d", &N, &M, &K);
    vector<vector<int> > cables(N);
    for (int i = 0; i < M; i++) {
      int c;
      scanf("%d", &c);
      for (int j = 0; j < c; j++) {
        int v;
        scanf("%d", &v);
        cables[v].push_back(i);
      }
    }

    vector<int> damaged;
    for (int i = 0; i < K; i++) {
      int v;
      scanf("%d", &v);
      for (vector<int>::const_iterator it = cables[v].begin(); it != cables[v].end(); ++it) {
        damaged.push_back(*it);
      }
    }
    sort(damaged.begin(), damaged.end());
    damaged.erase(unique(damaged.begin(), damaged.end()), damaged.end());
    int ans = N;
    for (int i = 0; i < N; i++) {
      for (vector<int>::const_iterator it = cables[i].begin(); it != cables[i].end(); ++it) {
        vector<int>::const_iterator jt = lower_bound(damaged.begin(), damaged.end(), *it);
        if (jt == damaged.end() || *jt != *it) {
          --ans;
          goto NEXT;
        }
      }
NEXT:
      ;
    }
    printf("%d\n", ans);

    scanf("%d %d %d", &N, &M, &K);
    if (N == -1) {
      break;
    }
  }
  return 0;
}
