#include <iostream>
#include <cstdio>
#include <cmath>
using namespace std;

double P, E, T;

double solve(int K, double L, double R)
{
  const double H = (L + R)/2.0;
  if (K == 0) {
    if (fabs(T - H) < E) {
      return 1.0;
    } else {
      return 0.0;
    }
  }

  if (R < T-E || T+E < L) {
    return 0.0;
  } else if (T-E <= L && R <= T+E) {
    return 1.0;
  }

  if (H <= T) {
    return P*solve(K-1, L, H) + (1.0-P)*solve(K-1, H, R);
  } else {
    return P*solve(K-1, H, R) + (1.0-P)*solve(K-1, L, H);
  }
}

int main()
{
  int K;
  double L, R;
  cin >> K >> L >> R;
  cin >> P >> E >> T;

  printf("%.6f\n", solve(K, L, R));
  return 0;
}
