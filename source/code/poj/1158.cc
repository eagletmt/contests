#include <cstdio>
#include <vector>
#include <queue>
using namespace std;

struct signal
{
  bool col;
  int ric, tb, tp;
  signal(bool a, int r, int b, int p) : col(a), ric(r), tb(b), tp(p) {}
  bool color(int t) const
  {
    if (t < ric) {
      return col;
    } else if (col) {
      // initial is B
      return (t - ric) % (tb + tp) >= tp;
    } else {
      // initial is P
      return (t - ric) % (tb + tp) < tb;
    }
  }
  int next_tick(int t) const
  {
    if (t < ric) {
      return ric;
    } else {
      const int u = (t - ric) % (tb + tp);
      if (col) {
        // initial is B
        if (u < tp) {
          return t + (tp - u);
        } else {
          return t + (tp + tb - u);
        }
      } else {
        // initial is P
        if (u < tb) {
          return t + (tb - u);
        } else {
          return t + (tb + tp - u);
        }
      }
    }
  }
};

int main()
{
  int src, dst;
  scanf("%d %d", &src, &dst);
  --src;  --dst;
  int N, M;
  scanf("%d %d", &N, &M);
  vector<signal> v;
  for (int i = 0; i < N; i++) {
    char c[2];
    int ric, tb, tp;
    scanf("%1s %d %d %d", c, &ric, &tb, &tp);
    v.push_back(signal(*c == 'B', ric, tb, tp));
  }
  vector<vector<pair<int,int> > > g(N);
  for (int i = 0; i < M; i++) {
    int u, w, l;
    scanf("%d %d %d", &u, &w, &l);
    --u;  --w;
    g[u].push_back(make_pair(w, l));
    g[w].push_back(make_pair(u, l));
  }

  priority_queue<pair<int,int> > q;
  q.push(make_pair(0, src));
  vector<int> dist(N, 10000000);
  dist[src] = 0;
  while (!q.empty()) {
    const int n = q.top().second;
    const int t = -q.top().first;
    q.pop();
    if (n == dst) {
      printf("%d\n", t);
      goto FINISH;
    }
    for (vector<pair<int,int> >::const_iterator it = g[n].begin(); it != g[n].end(); ++it) {
      const int m = it->first;
      const int l = it->second;
      int u = t;
      int c = 0;
      while (v[n].color(u) != v[m].color(u)) {
        const int a = v[n].next_tick(u);
        const int b = v[m].next_tick(u);
        if (a == b) {
          ++c;
          if (c == 3) {
            goto NEXT;
          }
        }
        u = min(a, b);
      }

      if (u+l < dist[m]) {
        dist[m] = u+l;
        q.push(make_pair(-u-l, m));
      }
NEXT:
      ;
    }
  }
  puts("0");
FINISH:
  return 0;
}
