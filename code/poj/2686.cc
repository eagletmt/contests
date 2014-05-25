#include <cstdio>
#include <vector>
#include <queue>
using namespace std;

struct state
{
  int city;
  double cost;
  unsigned ticket;
  state(int c, double d, unsigned t) : city(c), cost(d), ticket(t) {}
  bool operator<(const state& that) const
  {
    return cost > that.cost;
  }
};

int main()
{
  int N, M, P, A, B;
  while (scanf("%d%d%d%d%d", &N, &M, &P, &A, &B) != EOF && N != 0) {
    --A;  --B;
    static int tickets[8];
    for (int i = 0; i < N; i++) {
      scanf("%d", &tickets[i]);
    }
    vector<pair<int,int> > g[30];
    for (int i = 0; i < P; i++) {
      int x, y, z;
      scanf("%d%d%d", &x, &y, &z);
      --x;  --y;
      g[x].push_back(make_pair(y, z));
      g[y].push_back(make_pair(x, z));
    }

    static double dists[30][1<<8];
    for (int i = 0; i < M; i++) {
      fill_n(dists[i], 1<<N, 1e10);
    }
    dists[A][(1<<N)-1] = 0;
    priority_queue<state> q;
    q.push(state(A, 0.0, (1<<N)-1));
    while (!q.empty()) {
      const int n = q.top().city;
      const double cost = q.top().cost;
      const unsigned ticket = q.top().ticket;
      q.pop();
      if (n == B) {
        printf("%.3f\n", cost);
        goto NEXT;
      }

      for (vector<pair<int,int> >::const_iterator it(g[n].begin()); it != g[n].end(); ++it) {
        const int to = it->first;
        const int d = it->second;
        for (int i = 0; i < N; i++) {
          if (ticket & (1<<i)) {
            const unsigned s = ticket & ~(1<<i);
            const double c = cost + static_cast<double>(d) / tickets[i];
            if (c < dists[to][s]) {
              dists[to][s] = c;
              q.push(state(to, c, s));
            }
          }
        }
      }
    }
    puts("Impossible");
NEXT:
    ;
  }
  return 0;
}
