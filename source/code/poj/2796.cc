#include <cstdio>
#include <utility>
#include <queue>
using namespace std;
static const int M = 100000;
static const int K = 25;

int log2(int n)
{
  int c = 0;
  for (int x = 1; x <= n; x <<= 1) {
    ++c;
  }
  return c-1;
}

struct RMQ
{
  const int *v;
  int (*m)[K];
  int N;
  RMQ(const int *v_, int N_, int (*mem)[K])
    : v(v_), m(mem), N(N_)
  {
    for (int i = 0; i < N; i++) {
      m[i][0] = i;
    }
    for (int j = 1; (1<<j) <= N; j++) {
      for (int i = 0; i + (1<<j) - 1 < N; i++) {
        if (v[m[i][j-1]] < v[m[i+(1<<(j-1))][j-1]]) {
          m[i][j] = m[i][j-1];
        } else {
          m[i][j] = m[i + (1<<(j-1))][j-1];
        }
      }
    }
  }

  int query(int i, int j) const
  {
    const int k = log2(j - i + 1);
    if (v[m[i][k]] <= v[m[j-(1<<k)+1][k]]) {
      return m[i][k];
    } else {
      return m[j-(1<<k)+1][k];
    }
  }
};

pair<long long, pair<int,int> > solve(const int *v, const RMQ& m, const long long *sums, int beg, int end)
{
  queue<pair<int,int> > q;
  pair<long long, pair<int,int> > ans = make_pair((sums[end+1] - sums[beg]) * v[m.query(beg, end)], make_pair(beg, end));
  q.push(make_pair(beg, end));
  while (!q.empty()) {
    const int b = q.front().first;
    const int e = q.front().second;
    const int i = m.query(b, e);
    const long long x = (sums[e+1] - sums[b]) * v[i];
    q.pop();
    if (x > ans.first) {
      ans.first = x;
      ans.second = make_pair(b, e);
    }
    if (b <= i-1) {
      q.push(make_pair(b, i-1));
    }
    if (i+1 <= e) {
      q.push(make_pair(i+1, e));
    }
  }
  return ans;
}

int main()
{
  int N;
  scanf("%d", &N);
  static int v[M];
  for (int i = 0; i < N; i++) {
    scanf("%d", &v[i]);
  }

  static int mem[M][K];
  RMQ rmq(v, N, mem);

  static long long sums[M+1];
  for (int i = 0; i < N; i++) {
    sums[i+1] = sums[i] + v[i];
  }

  const pair<long long, pair<int,int> > ans = solve(v, rmq, sums, 0, N-1);
  printf("%lld\n", ans.first);
  printf("%d %d\n", ans.second.first+1, ans.second.second+1);
  return 0;
}
