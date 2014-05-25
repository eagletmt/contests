#include <iostream>
#include <vector>
#include <complex>
#include <cmath>
#include <algorithm>
using namespace std;
typedef complex<double> P;

double total_dist(const vector<P>& ps, const P& p)
{
  double s = 0.0;
  for (vector<P>::const_iterator it = ps.begin(); it != ps.end(); ++it) {
    s += abs(*it - p);
  }
  return s;
}

int main()
{
  int N;
  cin >> N;
  vector<P> ps(N);
  for (int i = 0; i < N; i++) {
    cin >> ps[i].real() >> ps[i].imag();
  }
  double step = 10000.0;
  P p = ps[0];
  double m = total_dist(ps, p);
  for (int i = 0; i < 1000; i++) {
    static const int di[] = {-1, 1, 0, 0};
    static const int dj[] = {0, 0, -1, 1};
    P next[4];
    double ls[4];
    for (int d = 0; d < 4; d++) {
      next[d] = p + P(di[d]*step, dj[d]*step);
      ls[d] = total_dist(ps, next[d]);
    }
    const int j = distance(ls, min_element(ls, ls+4));
    m = ls[j];
    p = next[j];
    step /= 2.0;
  }
  cout << lround(m) << endl;
  return 0;
}
