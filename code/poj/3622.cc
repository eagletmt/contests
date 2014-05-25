#include <cstdio>
#include <set>
#include <algorithm>
using namespace std;

int main()
{
  int N, M;
  scanf("%d %d", &N, &M);
  typedef pair<long long, long long> pll;
  static pll ba[100000];
  for (int i = 0; i < N; i++) {
    scanf("%lld %lld", &ba[i].second, &ba[i].first);
  }
  static pll dc[100000];
  for (int i = 0; i < M; i++) {
    scanf("%lld %lld", &dc[i].second, &dc[i].first);
  }

  sort(ba, ba+N, greater<pll>());
  sort(dc, dc+M, greater<pll>());
  int j = 0;
  multiset<long long> s;
  long long ans = 0LL;
  for (int i = 0; i < N; i++) {
    for (; j < M && dc[j].first >= ba[i].first; j++) {
      s.insert(dc[j].second);
    }
    multiset<long long>::const_iterator it = s.lower_bound(ba[i].second);
    if (it == s.end()) {
      ans = -1LL;
      break;
    } else {
      ans += *it;
      s.erase(it);
    }
  }
  printf("%lld\n", ans);
  return 0;
}
