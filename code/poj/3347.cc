#include <iostream>
#include <vector>
#include <iterator>
#include <cmath>
using namespace std;
static const double SQRT2 = sqrt(2.0);
static const double EPS = 1e-6;

bool ok(const vector<int>& s, const vector<double>& b, int k, double p)
{
  const double y = s[k]/SQRT2;
  const double x = p - y;
  for (int i = 0; i < k; i++) {
    if (x-b[i] <= y && y <= -x+b[i]+SQRT2*s[i]) {
      return false;
    }
  }
  return true;
}

int main()
{
  int N;
  while (cin >> N && N != 0) {
    vector<int> s(N);
    for (int i = 0; i < N; i++) {
      cin >> s[i];
    }
    vector<double> b(N);
    b[0] = s[0] / SQRT2;
    for (int i = 1; i < N; i++) {
      double left = max(b[i-1], s[i]/SQRT2), right = 1e5;
      for (int j = 0; j < 100; j++) {
        const double mid = (left + right)/2.0;
        if (ok(s, b, i, mid)) {
          right = mid;
        } else {
          left = mid;
        }
      }
      b[i] = (left + right)/2.0;
    }

    bool first = true;
    for (int i = 0; i < N; i++) {
      double l = b[i] - s[i]/SQRT2;
      double r = b[i] + s[i]/SQRT2;
      for (int j = 0; j < N; j++) {
        if (j < i) {
          l = max(l, b[j] + s[j]/SQRT2);
        } else if (i < j) {
          r = min(r, b[j] - s[j]/SQRT2);
        }
      }
      if (r - l > EPS) {
        if (!first) {
          cout << " ";
        }
        first = false;
        cout << i+1;
      }
    }
    cout << endl;
  }
  return 0;
}
