#include <cstdio>
#include <map>
using namespace std;

int numbering(map<int,int>& m, int x)
{
  const map<int,int>::const_iterator it = m.find(x);
  if (it != m.end()) {
    return it->second;
  } else {
    const int n = m.size();
    m.insert(make_pair(x, n));
    return n;
  }
}

int main()
{
  int P;
  scanf("%d", &P);
  static const int M = 1000000;
  static int ids[M];
  map<int,int> m;
  for (int i = 0; i < P; i++) {
    int x;
    scanf("%d", &x);
    ids[i] = numbering(m, x);
  }
  const int size = m.size();
  static int cnt[M];
  const int *last = ids + P;
  const int *end = ids;
  for (int n = 0; end != last && n < size; ++end) {
    if (cnt[*end] == 0) {
      ++n;
    }
    ++cnt[*end];
  }
  const int *begin = ids;
  while (cnt[*begin] > 1) {
    --cnt[*begin];
    ++begin;
  }
  int ans = end - begin;

  for (; end != last; ++end) {
    ++cnt[*end];
    while (cnt[*begin] > 1) {
      --cnt[*begin];
      ++begin;
    }
    ans = min(ans, int(end - begin + 1));
  }
  printf("%d\n", ans);
  return 0;
}
