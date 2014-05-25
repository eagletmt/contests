#include <iostream>
#include <vector>
#include <complex>
#include <algorithm>
using namespace std;
typedef complex<double> P;
static const double EPS = 1e-6;

inline double dot(const P& a, const P& b) { return a.real()*b.real() + a.imag()*b.imag(); }
inline double cross(const P& a, const P& b) { return a.real()*b.imag() - b.real()*a.imag(); }

int ccw(const P& a, P b, P c)/*{{{*/
{
  b -= a;
  c -= a;
  if (cross(b, c) > EPS) {
    // counter clockwise
    return +1;
  } else if (cross(b, c) < -EPS) {
    // clockwise
    return -1;
  } else if (dot(b, c) < -EPS) {
    // c-a-b on line
    return +2;
  } else if (dot(b, b) + EPS < dot(c, c)) {
    // a-b-c on line
    return -2;
  } else {
    return 0;
  }
}/*}}}*/

struct segment/*{{{*/
{
  P a, b;
  segment() {}
  segment(const P& x, const P& y) : a(x), b(y) {}

  // AOJ 2402 Milkey Way
  inline double distance(const P& p) const
  {
    if (dot(b-a, p-a) < EPS) {
      return abs(p-a);
    } else if (dot(a-b, p-b) < EPS) {
      return abs(p-b);
    } else {
      return abs(cross(b-a, p-a))/abs(b-a);
    }
  }
};/*}}}*/

bool formed(const vector<P>& ps)
{
  const int N = ps.size();
  for (int i = 0; i < N; i++) {
    if (ccw(ps[i], ps[(i+1)%N], ps[(i+2)%N]) == -1) {
      return false;
    }
  }
  return true;
}

bool fit(double R, const P& o, const vector<P>& ps)
{
  const int N = ps.size();
  for (int i = 0; i < N; i++) {
    const segment s(ps[i], ps[(i+1)%N]);
    if (ccw(s.a, o, s.b) == 1) {
      return false;
    }
    if (s.distance(o) + EPS < R) {
      return false;
    }
  }
  return true;
}

int main()
{
  for (int N; cin >> N && N >= 3;) {
    double R;
    P o;
    cin >> R >> o.real() >> o.imag();
    vector<P> ps(N);
    for (int i = 0; i < N; i++) {
      cin >> ps[i].real() >> ps[i].imag();
    }

    // make it counter-clockwise
    for (int i = 0; i < N; i++) {
      if (ccw(ps[i], ps[(i+1)%N], ps[(i+2)%N]) == -1) {
        reverse(ps.begin(), ps.end());
      }
    }

    if (!formed(ps)) {
      cout << "HOLE IS ILL-FORMED" << endl;
    } else if (fit(R, o, ps)) {
      cout << "PEG WILL FIT" << endl;
    } else {
      cout << "PEG WILL NOT FIT" << endl;
    }
  }
  return 0;
}
