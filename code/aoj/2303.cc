#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>
#include <cmath>
using namespace std;
static const double EPS = 1e-7;

struct runner {
  int p, t, v;
};

int main()
{
  static double comb[55][55];
  for (int i = 0; i <= 50; i++) {
    comb[i][0] = 1.0;
  }
  for (int i = 1; i <= 50; i++) {
    for (int j = 1; j <= i; j++) {
      comb[i][j] = comb[i-1][j-1] + comb[i-1][j];
    }
  }

  int N, M, L;
  cin >> N >> M >> L;
  vector<runner> v;
  bool all_zero = true;
  for (int i = 0; i < N; i++) {
    runner r;
    cin >> r.p >> r.t >> r.v;
    v.push_back(r);
    if (r.v != 0) {
      all_zero = false;
    }
  }

  if (all_zero) {
    for (int i = 0; i < N; i++) {
      cout << "0.0000000" << endl;
    }
    return 0;
  }

  vector<vector<double> > ps(N, vector<double>(M+1));
  vector<vector<double> > ps_integral(N, vector<double>(M+1));
  vector<vector<double> > ts(N, vector<double>(M+1));
  for (int i = 0; i < N; i++) {
    for (int j = 0; j <= M; j++) {
      ps[i][j] = pow(v[i].p/100.0, j) * pow((100-v[i].p)/100.0, M-j) * comb[M][j];
      if (j == 0) {
        ps_integral[i][j] = ps[i][j];
      } else {
        ps_integral[i][j] = ps_integral[i][j-1] + ps[i][j];
      }
      ts[i][j] = double(L)/v[i].v + v[i].t*j;
    }
  }

  for (int i = 0; i < N; i++) {
    double ans = 0.0;
    for (int j = 0; j <= M; j++) {
      double p = 1.0;
      for (int k = 0; k < N; k++) {
        if (k != i) {
          int l = lower_bound(ts[k].begin(), ts[k].end(), ts[i][j]+EPS) - ts[k].begin();
          if (l != 0) {
            p *= (1.0 - ps_integral[k][l-1]);
          }
        }
      }
      ans += ps[i][j] * p;
    }
    printf("%.6f\n", ans + EPS);
  }
  return 0;
}
