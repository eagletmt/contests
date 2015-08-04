#include <cstdio>
#include <string>
#include <vector>
#include <queue>
using namespace std;

static const int dr[] = {-1, -1, -1, 0, 0, 1, 1, 1};
static const int dc[] = {-1, 0, 1, -1, 1, -1, 0, 1};

char check(const vector<string>& grid, int r, int c)
{
  const int N = grid.size();
  for (int d = 0; d < 8; d++) {
    const int i = r + dr[d], j = c + dc[d];
    if (0 <= i && i < N && 0 <= j && j < N && grid[i][j] == '*') {
      return '#';
    }
  }
  return '.';
}

int main()
{
  int T;
  scanf("%d", &T);
  for (int Ti = 1; Ti <= T; Ti++) {
    int N, M;
    scanf("%d %d", &N, &M);
    vector<string> grid(N, string(N, '?'));
    for (int i = 0; i < M; i++) {
      int r, c;
      scanf("%d %d", &r, &c);
      --r;  --c;
      grid[r][c] = '*';
    }
    queue<pair<int,int> > q;
    q.push(make_pair(N/2, N/2));
    while (!q.empty()) {
      const int r = q.front().first, c = q.front().second;
      q.pop();
      grid[r][c] = check(grid, r, c);
      if (grid[r][c] == '#') {
        continue;
      }
      for (int d = 0; d < 8; d++) {
        const int i = r + dr[d], j = c + dc[d];
        if (0 <= i && i < N && 0 <= j && j < N && grid[i][j] == '?') {
          grid[i][j] = '!';
          q.push(make_pair(i, j));
        }
      }
    }

    printf("Scenario #%d:\n", Ti);
    for (int i = 0; i < N; i++) {
      puts(grid[i].c_str());
    }
    putchar('\n');
  }
  return 0;
}
