#include <cstdio>
#include <vector>
#include <queue>
#include <map>
#include <algorithm>
using namespace std;

struct renamer
{
  map<int,int> m;
  int operator()(int n)
  {
    if (m.count(n)) {
      return m[n];
    } else {
      int id = m.size();
      m.insert(make_pair(n, id));
      return id;
    }
  }
};

void bfs(vector<int>& even, const vector<vector<int> >& g, int start)
{
  queue<int> q;
  q.push(start);
  even[start] = true;
  while (!q.empty()) {
    const int n = q.front();
    q.pop();
    for (vector<int>::const_iterator it = g[n].begin(); it != g[n].end(); ++it) {
      for (vector<int>::const_iterator jt = g[*it].begin(); jt != g[*it].end(); ++jt) {
        if (!even[*jt]) {
          even[*jt] = true;
          q.push(*jt);
        }
      }
    }
  }
}

bool ok(const vector<vector<int> >& even)
{
  const int K = even.size(), N = even[0].size();
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < K; j++) {
      if (!even[j][i]) {
        goto FAIL;
      }
    }
    return true;
FAIL:
    ;
  }
  return false;
}

int main()
{
  int T;
  scanf("%d", &T);
  while (T-- > 0) {
    int N, K;
    scanf("%d %d", &N, &K);
    vector<vector<int> > g(N);
    renamer r;
    for (int i = 0; i < N; i++) {
      int n, m;
      scanf("%d %d", &n, &m);
      const int u = r(n);
      for (int j = 0; j < m; j++) {
        int x;
        scanf("%d", &x);
        const int v = r(x);
        g[u].push_back(v);
        g[v].push_back(u);
      }
    }

    vector<vector<int> > even(K, vector<int>(N, 0));
    for (int i = 0; i < K; i++) {
      int n;
      scanf("%d", &n);
      bfs(even[i], g, r(n));
    }
    puts(ok(even) ? "YES" : "NO");
  }
  return 0;
}
