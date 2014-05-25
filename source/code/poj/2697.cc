#include <cstdio>
#include <vector>
#include <queue>
using namespace std;

struct quadruple { int a[4]; };
quadruple tbl1[1820], tbl2[495];
int rev_tbl1[16][16][16][16], rev_tbl2[16][16][16][16];
struct grid
{
  char a[4][5];
  void dump() {
    for (int i = 0; i < 4; i++) {
      puts(a[i]);
    }
  }
};

int encode(const grid& g)
{
  int ws[4], bs[4];
  int w = 0, b = 0;
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      if (g.a[i][j] == 'w') {
        ws[w++] = i*4+j;
      } else if (g.a[i][j] == 'b') {
        bs[b++] = i*4+j - w;
      }
    }
  }
  return rev_tbl1[ws[0]][ws[1]][ws[2]][ws[3]] * 495 + rev_tbl2[bs[0]][bs[1]][bs[2]][bs[3]];
}

void decode(grid &g, int n)
{
  const quadruple ws = tbl1[n/495], bs = tbl2[n%495];
  int w = 0, b = 0;
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      if (ws.a[w] == 4*i+j) {
        ++w;
        g.a[i][j] = 'w';
      } else if (bs.a[b]+w == 4*i+j) {
        ++b;
        g.a[i][j] = 'b';
      } else {
        g.a[i][j] = '*';
      }
    }
    g.a[i][4] = '\0';
  }
}

void init(quadruple *t, int r[16][16][16][16], int N)
{
  int c = 0;
  for (int i = 0; i < N; i++) {
    for (int j = i+1; j < N; j++) {
      for (int k = j+1; k < N; k++) {
        for (int l = k+1; l < N; l++) {
          t[c].a[0] = i;
          t[c].a[1] = j;
          t[c].a[2] = k;
          t[c].a[3] = l;
          r[i][j][k][l] = c;
          ++c;
        }
      }
    }
  }
}

int main()
{
  init(tbl1, rev_tbl1, 16);
  init(tbl2, rev_tbl2, 12);

  int T;
  scanf("%d", &T);
  while (T-- > 0) {
    grid start, goal;
    for (int i = 0; i < 4; i++) {
      scanf("%s", start.a[i]);
    }
    for (int i = 0; i < 4; i++) {
      scanf("%s", goal.a[i]);
    }
    const int e_goal = encode(goal);
    static const int SIZE = 900900;
    static int dist[SIZE];
    static const int INF = 100000000;
    fill_n(dist, SIZE, INF);
    queue<int> q;
    q.push(encode(start));
    dist[q.front()] = 0;
    while (!q.empty()) {
      const int n = q.front();
      q.pop();
      if (n == e_goal) {
        printf("%d\n", dist[n]);
        goto NEXT;
      }

      grid g;
      decode(g, n);
      for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
          static char wb[] = {'w', 'b'};
          if (g.a[i][j] != wb[dist[n]&1]) {
            continue;
          }
          for (int a = 0; a < 8; a++) {
            static const int di[] = {-1, -1, 0, 1, 1, 1, 0, -1};
            static const int dj[] = {0, 1, 1, 1, 0, -1, -1, -1};
            int k = i, l = j;
            while (true) {
              const int x = k + di[a];
              const int y = l + dj[a];
              if (0 <= x && x < 4 && 0 <= y && y < 4 && g.a[x][y] == '*') {
                // ok
              } else {
                break;
              }
              if (a % 2 == 1) {
                // diag
                if (g.a[k][y] != '*' || g.a[x][l] != '*') {
                  break;
                }
              }
              k = x;
              l = y;
            }
            swap(g.a[k][l], g.a[i][j]);
            const int e = encode(g);
            if (dist[n]+1 < dist[e]) {
              dist[e] = dist[n]+1;
              q.push(e);
            }
            swap(g.a[k][l], g.a[i][j]);
          }
        }
      }
    }
    puts("-1");
NEXT:
    ;
  }
  return 0;
}
