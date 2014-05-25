#include <cstdio>
#include <vector>
using namespace std;

bool ok(const vector<long long>& cables, int K, long long len)
{
  if (len == 0) {
    return true;
  }
  for (vector<long long>::const_iterator it(cables.begin()); it != cables.end() && K > 0; ++it) {
    K -= *it / len;
  }
  return K <= 0;
}

int main()
{
  int N, K;
  scanf("%d %d", &N, &K);
  vector<long long> cables(N);
  long long right = 0LL;
  for (int i = 0; i < N; i++) {
    double d;
    scanf("%lf", &d);
    cables[i] = 100LL*d;
    right = max(right, cables[i]);
  }
  long long left = 0;
  while (left < right) {
    if (left+1 == right) {
      if (ok(cables, K, right)) {
        left = right;
      }
      break;
    }
    const long long mid = (left + right) / 2LL;
    if (ok(cables, K, mid)) {
      left = mid;
    } else {
      right = mid;
    }
  }
  printf("%lld.%02lld\n", left/100, left%100);
  return 0;
}
