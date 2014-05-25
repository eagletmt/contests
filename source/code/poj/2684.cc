#include <iostream>
#include <vector>
#include <complex>
#include <algorithm>
using namespace std;
typedef complex<int> P;

namespace std {
  bool operator<(const P& p, const P& q)
  {
    if (p.real() == q.real()) {
      return p.imag() < q.imag();
    } else {
      return p.real() < q.real();
    }
  }
};

void rotate(vector<P>& v)
{
  for (vector<P>::iterator it(v.begin()); it != v.end(); ++it) {
    *it = P(0, 1) * *it;
  }
}

bool fit(const vector<P>& a, const vector<P>& b)
{
  const int dx = a[0].real() - b[0].real();
  const int dy = a[0].imag() - b[0].imag();
  for (int j = 1; j < a.size(); j++) {
    const int x = a[j].real() - b[j].real();
    const int y = a[j].imag() - b[j].imag();
    if (x != dx || y != dy) {
      return false;
    }
  }
  return true;
}

bool is_same(vector<P> base, vector<P> p)
{
  if (base.size() != p.size()) {
    return false;
  }
  for (int i = 0; i < 4; i++) {
    vector<P> v(p);
    if (fit(base, v)) {
      return true;
    }
    reverse(v.begin(), v.end());
    if (fit(base, v)) {
      return true;
    }
    reverse(base.begin(), base.end());
    if (fit(base, v)) {
      return true;
    }
    reverse(v.begin(), v.end());
    if (fit(base, v)) {
      return true;
    }
    reverse(base.begin(), base.end());
    rotate(p);
  }
  return false;
}

int main()
{
  int N;
  while (cin >> N && N != 0) {
    int m;
    cin >> m;
    vector<P> base(m);
    for (int i = 0; i < m; i++) {
      cin >> base[i].real() >> base[i].imag();
    }

    for (int i = 0; i < N; i++) {
      cin >> m;
      vector<P> v(m);
      for (int j = 0; j < m; j++) {
        cin >> v[j].real() >> v[j].imag();
      }
      if (is_same(base, v)) {
        cout << i+1 << endl;
      }
    }
    cout << "+++++" << endl;
  }
  return 0;
}
