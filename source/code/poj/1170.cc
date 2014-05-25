#include <cstdio>
#include <queue>
using namespace std;
static const int K = 6;

int encode(const int *v, int B)
{
  int x = 0;
  for (int i = 0; i < B; i++) {
    x = K*x + v[i];
  }
  return x;
}

void decode(int *v, int B, int x)
{
  for (int i = B-1; i >= 0; i--) {
    v[i] = x % K;
    x /= K;
  }
}

int main()
{
  int B;
  scanf("%d", &B);
  int ks[5], ps[5];
  static int m[1000];
  for (int i = 0; i < B; i++) {
    int c;
    scanf("%d %d %d", &c, &ks[i], &ps[i]);
    m[c] = i;
  }

  int S;
  scanf("%d", &S);
  static int os[100][5];
  int ops[100];
  for (int i = 0; i < S; i++) {
    int N;
    scanf("%d", &N);
    for (int j = 0; j < N; j++) {
      int c, k;
      scanf("%d %d", &c, &k);
      os[i][m[c]] = k;
    }
    scanf("%d", &ops[i]);
  }

  static const int INF = 10000000;
  static int dist[7776];
  fill_n(dist, 7776, INF);
  priority_queue<pair<int, int> > q;
  q.push(make_pair(0, encode(ks, B)));
  dist[encode(ks, B)] = 0;
  int ans = INF;
  while (!q.empty()) {
    const int c = -q.top().first;
    const int ve = q.top().second;
    q.pop();
    int v[5];
    decode(v, B, ve);

    if (c > dist[ve]) {
      continue;
    }

    int a = c;
    for (int i = 0; i < B; i++) {
      a += ps[i] * v[i];
    }
    ans = min(ans, a);

    for (int i = 0; i < S; i++) {
      int w[5];
      copy(v, v+B, w);
      const int cc = c + ops[i];
      int we;
      for (int j = 0; j < B; j++) {
        w[j] = v[j] - os[i][j];
        if (w[j] < 0) {
          goto SKIP;
        }
      }
      we = encode(w, B);
      if (cc < dist[we]) {
        dist[we] = cc;
        q.push(make_pair(-cc, we));
      }
SKIP:
      ;
    }
  }
  printf("%d\n", ans);
  return 0;
}
