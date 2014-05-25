#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;

int main()
{
  int T;
  scanf("%d", &T);
  while (T-- > 0) {
    int id, M;
    scanf("%d %d", &id, &M);
    vector<int> v(M);
    for (int i = 0; i < M; i++) {
      scanf("%d", &v[i]);
    }
    const vector<int> w = v;
    sort(v.begin(), v.end());

    vector<int> ans((M+1)/2);
    ans[(M-1)/2] = v[(M-1)/2];
    for (int i = M-1; i > 0; i -= 2) {
      vector<int>::iterator it = lower_bound(v.begin(), v.end(), w[i]);
      v.erase(it);
      it = lower_bound(v.begin(), v.end(), w[i-1]);
      v.erase(it);
      ans[(i-1)/2] = v[(i-1)/2];
    }

    printf("%d %d", id, (M+1)/2);
    for (int i = 0; i <= (M-1)/2; i++) {
      if (i % 10 == 0) {
        printf("\n%d", ans[i]);
      } else {
        printf(" %d", ans[i]);
      }
    }
    putchar('\n');
  }
  return 0;
}
