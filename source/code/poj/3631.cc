#include <cstdio>
#include <algorithm>
using namespace std;
static const int MAXN = 10000;

int h[MAXN][2];
int tbl[MAXN];
bool visited[MAXN];

bool insert(int x)
{
  for (int i = 0; i < 2; i++) {
    int k = h[x][i];
    if (!visited[k]) {
      visited[k] = true;
      if (tbl[k] == -1 || insert(tbl[k])) {
        tbl[k] = x;
        return true;
      }
    }
  }
  return false;
}

void solve(int N, int M)
{
  for (int i = 0; i < M; i++) {
    fill_n(visited, N, false);
    if (!insert(i)) {
      puts("rehash necessary");
      return;
    }
  }
  puts("successful hashing");
}

int main()
{
  int T;
  scanf("%d", &T);
  while (T-- > 0) {
    int M, N;
    scanf("%d %d", &M, &N);
    for (int i = 0; i < M; i++) {
      scanf("%d %d", &h[i][0], &h[i][1]);
    }
    fill_n(tbl, N, -1);
    solve(N, M);
  }
  return 0;
}
