#include <cstdio>
#include <algorithm>
using namespace std;

int main()
{
  int N;
  scanf("%d", &N);
  static pair<int,int> is[50000];
  for (int i = 0; i < N; i++) {
    scanf("%d %d", &is[i].first, &is[i].second);
  }
  sort(is, is+N);

  pair<int,int> r = is[0];
  for (int i = 1; i < N; i++) {
    if (r.second < is[i].first) {
      printf("%d %d\n", r.first, r.second);
      r = is[i];
    } else {
      r.second = max(r.second, is[i].second);
    }
  }
  printf("%d %d\n", r.first, r.second);
  return 0;
}
