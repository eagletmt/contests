#include <cstdio>
#include <vector>
using namespace std;
static const int INF = 10000000;

bool bm_augment(const vector<int> *g, int u, int *match_to, int *visited) // {{{
{
  if (u < 0) {
    return true;
  }

  for (vector<int>::const_iterator it(g[u].begin()); it != g[u].end(); ++it) {
    if (!visited[*it]) {
      visited[*it] = true;
      if (bm_augment(g, match_to[*it], match_to, visited)) {
        match_to[u] = *it;
        match_to[*it] = u;
        return true;
      }
    }
  }
  return false;
} // }}}

int bipartite_matching(const vector<int> *g, int N)  // {{{
{
  static int match_to[500];
  fill_n(match_to, N, -1);
  int match = 0;
  for (int u = 0; u < N; u++) {
    static int visited[500];
    fill_n(visited, N, 0);
    if (bm_augment(g, u, match_to, visited)) {
      match++;
    }
  }
  return match;
} // }}}

bool defeat(const pair<int,int>& human, const pair<int,int>& alien, int d, int T)
{
  const int t = T - d;
  if (t < 0) {
    return false;
  }
  if (human.first - d*human.second >= alien.first) {
    const int h = human.first;
    const int a = alien.first + d*alien.second;
    return h >= a;
  } else {
    const long long h = human.first + static_cast<long long>(t)*human.second;
    const long long a = alien.first + static_cast<long long>(T)*alien.second;
    return h >= a;
  }
}

bool ok(const pair<int,int> *humans, int H, const pair<int,int> *aliens, int A, const int dist[250][250], int T)
{
  static vector<int> g[500];
  for (int i = 0; i < A+H; i++) {
    g[i].clear();
  }
  for (int i = 0; i < H; i++) {
    for (int j = 0; j < A; j++) {
      if (defeat(humans[i], aliens[j], dist[i][j], T)) {
        g[i].push_back(H+j);
      }
    }
  }
  return bipartite_matching(g, A+H) == A;
}

int main()
{
  int H, A;
  while (scanf("%d %d", &H, &A) != EOF && H != 0) {
    static pair<int,int> humans[250], aliens[250];
    for (int i = 0; i < H; i++) {
      scanf("%d %d", &humans[i].first, &humans[i].second);
    }
    for (int i = 0; i < A; i++) {
      scanf("%d %d", &aliens[i].first, &aliens[i].second);
    }

    static int dist[250][250];
    for (int i = 0; i < H; i++) {
      for (int j = 0; j < A; j++) {
        scanf("%d", &dist[i][j]);
      }
    }
    int lo = 0, hi = INF;
    while (lo+1 < hi) {
      const int mid = (lo + hi)/2;
      if (ok(humans, H, aliens, A, dist, mid)) {
        hi = mid;
      } else {
        lo = mid;
      }
    }
    if (!ok(humans, H, aliens, A, dist, lo)) {
      lo = hi;
    }
    if (lo == INF) {
      puts("IMPOSSIBLE");
    } else {
      printf("%d\n", lo);
    }
  }
  return 0;
}
