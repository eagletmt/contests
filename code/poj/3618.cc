#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;

int main()
{
  int N;
  long long T;
  scanf("%lld %d", &T, &N);
  vector<int> left, right;
  for (int i = 0; i < N; i++) {
    int x;
    scanf("%d", &x);
    if (x >= 0) {
      right.push_back(x);
    } else {
      left.push_back(-x);
    }
  }
  sort(right.begin(), right.end());
  sort(left.begin(), left.end());

  vector<int>::const_iterator it = right.begin(), jt = left.begin();
  int ans = 0;
  int pos = 0;
  for (int i = 0; i < N && T > 0LL; i++) {
    if (it == right.end()) {
      T -= abs(pos + *jt);
      pos = -*jt;
      ++jt;
    } else if (jt == left.end()) {
      T -= abs(pos - *it);
      pos = *it;
      ++it;
    } else if (*it < *jt) {
      T -= abs(pos - *it);
      pos = *it;
      ++it;
    } else {
      T -= abs(pos + *jt);
      pos = -*jt;
      ++jt;
    }
    if (T >= 0LL) {
      ++ans;
    }
  }
  printf("%d\n", ans);
  return 0;
}
