#include <cstdio>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

int main()
{
  int N;
  while (scanf("%d", &N) != EOF) {
    if (N == 0) {
      puts("0");
      continue;
    }
    vector<pair<int,int> > v(N);
    for (int i = 0; i < N; i++) {
      scanf("%d %d", &v[i].second, &v[i].first);
    }
    sort(v.rbegin(), v.rend());
    long long ans = 0LL;
    priority_queue<int> q;
    vector<pair<int,int> >::const_iterator it = v.begin();
    for (int d = it->first; d > 0; d--) {
      while (it != v.end() && it->first == d) {
        q.push(it->second);
        ++it;
      }
      if (!q.empty()) {
        ans += static_cast<long long>(q.top());
        q.pop();
      }
    }
    printf("%lld\n", ans);
  }
  return 0;
}
