#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;

int main()
{
  int N, M;
  for (int Ti = 1; scanf("%d %d", &M, &N) != EOF && M != 0; Ti++) {
    vector<int> v(N);
    for (int i = 0; i < N; i++) {
      scanf("%d", &v[i]);
    }

    sort(v.rbegin(), v.rend());
    int ans = 0;
    int c = 0;
    vector<int>::const_iterator it = v.begin();
    for (int i = N*M; it != v.end(); i--) {
      if (*it == i) {
        if (c == 0) {
          ++ans;
        } else {
          --c;
        }
        ++it;
      } else {
        ++c;
      }
    }
    printf("Case %d: %d\n", Ti, ans);
  }
  return 0;
}
