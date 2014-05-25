#include <iostream>
#include <cstdio>
#include <vector>
using namespace std;

struct color
{
  double L, a, b;
};

inline double sqr(double x) { return x*x; }
inline double operator-(const color& lhs, const color& rhs)
{
  return sqr(lhs.L - rhs.L) + sqr(lhs.a - rhs.a) + sqr(lhs.b - rhs.b);
}

int main()
{
  int N, M;
  cin >> N >> M;
  vector<color> cs;
  for (int i = 0; i < N; i++) {
    color c;
    cin >> c.L >> c.a >> c.b;
    cs.push_back(c);
  }

  double ans = 0.0;
  for (int s = 0; s < (1<<N); s++) {
    vector<color> v;
    for (int i = 0; i < N; i++) {
      if (s & (1<<i)) {
        v.push_back(cs[i]);
      }
    }
    if (v.size() != M) {
      continue;
    }

    double x = 0.0;
    for (vector<color>::const_iterator it = v.begin(); it != v.end(); ++it) {
      for (vector<color>::const_iterator jt = it+1; jt != v.end(); ++jt) {
        x += *it - *jt;
      }
    }
    ans = max(ans, x);
  }
  printf("%.6f\n", ans);
  return 0;
}
