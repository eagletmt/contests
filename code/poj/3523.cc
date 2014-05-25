#include <cstdio>
#include <map>
#include <queue>
#include <algorithm>
using namespace std;
static const int di[] = {0, -1, 1, 0, 0}, dj[] = {0, 0, 0, -1, 1};

inline int h(int s, const unsigned short hh[3][256], int N)
{
  unsigned short l = 0;
  for (int i = 0; i < N; i++) {
    l = max(l, hh[i][(s>>(i<<3))&0xff]);
  }
  return l;
}

int calc_next(int N, const char grid[16][20], int s, int *a)
{
  int next = 0;
  for (int i = 0; i < N; i++) {
    const int t = (s>>(i<<3))&0xff;
    const int k = (t>>4) + di[a[i]];
    const int l = (t&0xf) + dj[a[i]];
    if (grid[k][l] == '#') {
      return -i-1;
    }
    const int u = (k<<4)|l;
    const int v = (s>>(i<<3))&0xff;
    for (int j = 0; j < i; j++) {
      const int w = (next>>(j<<3))&0xff;
      if (u == w) {
        return 0;
      }
      if (u == ((s>>(j<<3))&0xff) && w == v) {
        return 0;
      }
    }
    next |= u<<(i<<3);
  }
  return next;
}

inline int get(int s, const unsigned char *d1, const map<int,short>& d2)
{
  int d = d1[s];
  if (d == 255) {
    return 1000;
  } else if (d == 254) {
    return d2.find(s)->second;
  } else {
    return d;
  }
}

inline void set(int s, unsigned char *d1, map<int,short>& d2, int d)
{
  if (d >= 254) {
    d1[s] = 254;
    d2[s] = d;
  } else {
    d1[s] = d;
  }
}

int main()
{
  char buf[100];
  while (fgets(buf, sizeof buf, stdin)) {
    int W, H, N;
    sscanf(buf, "%d %d %d", &W, &H, &N);
    if (N == 0) {
      break;
    }
    char grid[16][20];
    int init = 0, final = 0;
    for (int i = 0; i < H; i++) {
      fgets(grid[i], 20, stdin);
      for (int j = 0; j < W; j++) {
        if ('a' <= grid[i][j] && grid[i][j] <= 'c') {
          init |= (i<<4|j) << ((grid[i][j]-'a')<<3);
          grid[i][j] = ' ';
        } else if ('A' <= grid[i][j] && grid[i][j] <= 'C') {
          final |= (i<<4|j) << ((grid[i][j]-'A')<<3);
          grid[i][j] = ' ';
        }
      }
    }
    const int A = N >= 0 ? 5 : 1;
    const int B = N >= 1 ? 5 : 1;
    const int C = N >= 2 ? 5 : 1;

    static unsigned short int hh[3][256];
    for (int i = 0; i < N; i++) {
      fill_n(hh[i], 256, 1000);
      queue<int> q;
      q.push((final>>(i<<3))&0xff);
      hh[i][(final>>(i<<3))&0xff] = 0;
      while (!q.empty()) {
        const int s = q.front();
        const int x = s>>4;
        const int y = s&0xf;
        q.pop();
        for (int d = 1; d < 5; d++) {
          const int k = x + di[d];
          const int l = y + dj[d];
          const int t = (k<<4)|l;
          if (grid[k][l] != '#' && hh[i][s]+1 < hh[i][t]) {
            hh[i][t] = hh[i][s]+1;
            q.push(t);
          }
        }
      }
    }

    static unsigned char dist[256*256*256];
    fill_n(dist, 256*256*256, 255);
    map<int,short> dist2;
    dist[init] = 0;
    priority_queue<pair<short,int> > q;
    q.push(make_pair(-h(init, hh, N), init));
    while (!q.empty()) {
      const int cost = -q.top().first;
      const int s = q.top().second;
      q.pop();
      if (s == final) {
        printf("%d\n", cost);
        break;
      }
      const int d = cost - h(s, hh, N);
      const int d2 = get(s, dist, dist2);
      if (d > d2) {
        continue;
      }

      bool inv[5] = {false, false, false, false, false};
      int a[3];
      for (a[0] = 0; a[0] < A; a[0]++) {
        for (a[1] = 0; a[1] < B; a[1]++) {
          if (inv[a[1]]) {
            continue;
          }
          for (a[2] = 0; a[2] < C; a[2]++) {
            const int next = calc_next(N, grid, s, a);
            if (next == 0) {
              continue;
            } else if (next < 0) {
              if (next == -1) {
                goto SKIP_A;
              } else if (next == -2) {
                inv[a[1]] = true;
                goto SKIP_B;
              } else {
                continue;
              }
            }
            const int du = get(next, dist, dist2);
            if (d+1 < du) {
              set(next, dist, dist2, d+1);
              q.push(make_pair(-d-1-h(next, hh, N), next));
            }
          }
SKIP_B:
          ;
        }
SKIP_A:
        ;
      }
    }
  }
  return 0;
}
