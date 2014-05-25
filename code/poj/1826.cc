#include <cstdio>
#include <map>
#include <queue>
#include <algorithm>
using namespace std;
typedef long long ll;

int main()
{
  static const ll GETA = 40000, T = 100000;
  int N;
  while (scanf("%d", &N) != EOF && N != 0) {
    map<ll, int> m;
    for (int i = 0; i < N; i++) {
      int x, y, val;
      scanf("%d %d %d", &x, &y, &val);
      m.insert(make_pair((x+GETA)*T + y+GETA, val));
    }

    int ans = 0;
    while (!m.empty()) {
      map<ll, int>::iterator jt = m.begin();
      queue<ll> q;
      int val = jt->second;
      q.push(jt->first);
      m.erase(jt);
      while (!q.empty()) {
        const ll pos = q.front();
        q.pop();
        const int i = pos/T, j = pos%T;
        for (int d = 0; d < 4; d++) {
          static const int di[] = {-1, 1, 0, 0}, dj[] = {0, 0, -1, 1};
          const ll next = (i+di[d])*T + j+dj[d];
          jt = m.find(next);
          if (jt != m.end()) {
            val += jt->second;
            q.push(jt->first);
            m.erase(jt);
          }
        }
      }
      ans = max(ans, val);
    }
    printf("%d\n", ans);
  }
  return 0;
}
