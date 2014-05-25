#include <cstdio>
#include <vector>
#include <queue>
#include <algorithm>
#include <limits>
using namespace std;
static const int MAXN = 3010;

template <class Flow, class Cost>
struct node
{
  int index;
  Flow capacity;
  Cost cost;
  node(int i, Flow c, Cost d) : index(i), capacity(c), cost(d) {}
};

template <class Flow, class Cost>
node<Flow, Cost> make_node(int i, Flow c, Cost d) { return node<Flow, Cost>(i, c, d); }

template <class Flow, class Cost>
pair<Flow, Cost>
primal_dual(const vector<node<Flow, Cost> > *g, int N, int source, int sink)/*{{{*/
{
  static Flow capacity[MAXN][MAXN], flow[MAXN][MAXN];
  static Cost cost[MAXN][MAXN];
  for (int i = 0; i < N; i++) {
    for (typename vector<node<Flow, Cost> >::const_iterator it(g[i].begin()); it != g[i].end(); ++it) {
      capacity[i][it->index] += it->capacity;
      cost[i][it->index] += it->cost;
    }
  }
  pair<Flow, Cost> total;
  static Cost h[MAXN], dist[MAXN];
  static int parent[MAXN];
  for (Flow f = numeric_limits<Flow>::max(); f > 0; ) {
    fill_n(dist, N, 1000000);
    dist[source] = 0;
    fill_n(parent, N, -1);
    priority_queue<pair<Cost,int> > q;
    q.push(make_pair(0, source));
    while (!q.empty()) {
      const int n = q.top().second;
      const Cost c = -q.top().first;
      q.pop();
      if (dist[n] < c) {
        continue;
      }
      for (typename vector<node<Flow, Cost> >::const_iterator it = g[n].begin(); it != g[n].end(); ++it) {
        if (capacity[n][it->index] - flow[n][it->index] > 0) {
          const Cost c2 = c + cost[n][it->index] + h[n] - h[it->index];
          if (c2 < dist[it->index]) {
            dist[it->index] = c2;
            parent[it->index] = n;
            q.push(make_pair(-c2, it->index));
          }
        }
      }
    }
    if (parent[sink] == -1) {
      break;
    }

    Flow e = f;
    for (int i = sink; i != source; i = parent[i]) {
      e = min(e, capacity[parent[i]][i] - flow[parent[i]][i]);
    }
    for (int i = sink; i != source; i = parent[i]) {
      total.second += e * cost[parent[i]][i];
      flow[i][parent[i]] -= e;
      flow[parent[i]][i] += e;
    }
    f -= e;
    total.first += e;
    for (int i = 0; i < N; i++) {
      h[i] += dist[i];
    }
  }

  return total;
}/*}}}*/

int main()
{
  int N;
  scanf("%d", &N);
  static pair<int,int> blocks[1000];
  vector<int> v;
  for (int i = 0; i < N; i++) {
    scanf("%d %d", &blocks[i].first, &blocks[i].second);
    v.push_back(blocks[i].first);
    v.push_back(blocks[i].second);
  }
  sort(v.begin(), v.end());

  static vector<node<int, long long> > g[MAXN];
  const int source = N + v.size();
  const int sink = source + 1;
  const int dummy = sink + 1;
  for (int i = 0; i < N; i++) {
    const long long a = blocks[i].first, b = blocks[i].second;
    const int j = lower_bound(v.begin(), v.end(), a) - v.begin();
    const int k = lower_bound(v.begin(), v.end(), b) - v.begin();
    g[source].push_back(make_node(i, 1, 0LL));
    g[i].push_back(make_node(source, 0, 0LL));

    g[i].push_back(make_node(dummy, 1, 0LL));
    g[dummy].push_back(make_node(i, 0, 0LL));

    g[i].push_back(make_node(N+j, 1, -b));
    g[N+j].push_back(make_node(i, 0, b));
    if (b != a) {
      g[i].push_back(make_node(N+k, 1, -a));
      g[N+k].push_back(make_node(i, 0, a));
    }
  }
  for (vector<int>::size_type i = 0; i < v.size(); i++) {
    g[N+i].push_back(make_node(sink, 1, 0LL));
    g[sink].push_back(make_node(N+i, 0, 0LL));
  }
  g[dummy].push_back(make_node(sink, N, 0LL));

  printf("%lld\n", -primal_dual(g, dummy+1, source, sink).second);
  return 0;
}
