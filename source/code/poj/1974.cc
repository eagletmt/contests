#include <cstdio>
#include <algorithm>
using namespace std;

int countup(pair<int,int> *first, pair<int,int> *last)
{
  sort(first, last);
  int n = 0;
  int r = first->first;
  int c = first->second;
  for (pair<int,int> *it = first+1; it != last; ++it) {
    if (it->first == r && it->second - c > 2) {
      ++n;
    }
    r = it->first;
    c = it->second;
  }
  return n;
}

int main()
{
  int T;
  scanf("%d", &T);
  while (T-- > 0) {
    int M, N, K;
    scanf("%d %d %d", &M, &N, &K);
    static pair<int,int> a[700000];
    for (int i = 0; i < K; i++) {
      scanf("%d %d", &a[i].first, &a[i].second);
    }
    pair<int,int> *p = a+K;
    for (int i = 1; i <= M; i++) {
      p->first = i;
      p->second = 0;
      ++p;
      p->first = i;
      p->second = N+1;
      ++p;
    }
    for (int i = 1; i <= N; i++) {
      p->first = 0;
      p->second = i;
      ++p;
      p->first = M+1;
      p->second = i;
      ++p;
    }
    int ans = countup(a, p);
    for (pair<int,int> *it = a; it != p; ++it) {
      swap(it->first, it->second);
    }
    ans += countup(a, p);
    printf("%d\n", ans);
  }
  return 0;
}
