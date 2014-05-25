#include <cstdio>
#include <string>
#include <vector>
#include <map>
using namespace std;

bool ok(const map<string, vector<pair<int,long long> > >& m, long long B, long long Q)
{
  long long b = 0LL;
  for (map<string, vector<pair<int,long long> > >::const_iterator it = m.begin(); it != m.end(); ++it) {
    const vector<pair<int,long long> >& v = it->second;
    static const long long INF = 1LL<<60;
    long long x = INF;
    for (vector<pair<int,long long> >::const_iterator jt = v.begin(); jt != v.end(); ++jt) {
      if (jt->second >= Q) {
        x = min(x, static_cast<long long>(jt->first));
      }
    }
    if (b == INF) {
      return false;
    }
    b += x;
    if (b > B) {
      return false;
    }
  }
  return b <= B;
}

int main()
{
  int T;
  scanf("%d", &T);
  while (T-- > 0) {
    int N;
    long long B;
    scanf("%d %lld", &N, &B);
    map<string, vector<pair<int,long long> > > m;
    for (int i = 0; i < N; i++) {
      char type[30], name[30];
      int price;
      long long quality;
      scanf("%s %s %d %lld", type, name, &price, &quality);
      m[type].push_back(make_pair(price, quality));
    }

    long long left = 0LL, right = 1000000000LL;
    while (left < right) {
      const long long mid = (left + right)/2LL;
      if (ok(m, B, mid)) {
        left = mid+1;
      } else {
        right = mid;
      }
    }
    printf("%lld\n", left-1LL);
  }
  return 0;
}
