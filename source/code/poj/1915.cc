#include <cstdio>
#include <queue>
#include <algorithm>
using namespace std;

int main()
{
  int T;
  scanf("%d", &T);
  while (T-- > 0) {
    int L;
    scanf("%d", &L);
    pair<int,int> start, goal;
    scanf("%d %d", &start.first, &start.second);
    scanf("%d %d", &goal.first, &goal.second);
    static int dist[300][300];
    static const int INF = 10000000;
    for (int i = 0; i < L; i++) {
      fill_n(dist[i], L, INF);
    }
    dist[start.first][start.second] = 0;
    queue<pair<int,int> > q;
    q.push(start);
    while (!q.empty()) {
      const int i = q.front().first;
      const int j = q.front().second;
      q.pop();
      for (int d = 0; d < 8; d++) {
        static const int di[] = {-2, -1, 1, 2, 2, 1, -1, -2};
        static const int dj[] = {1, 2, 2, 1, -1, -2, -2, -1};
        const int k = i + di[d];
        const int l = j + dj[d];
        if (0 <= k && k < L && 0 <= l && l < L && dist[i][j]+1 < dist[k][l]) {
          dist[k][l] = dist[i][j]+1;
          q.push(make_pair(k, l));
        }
      }
    }
    printf("%d\n", dist[goal.first][goal.second]);
  }
  return 0;
}
