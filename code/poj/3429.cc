#include <iostream>
#include <vector>
#include <complex>
using namespace std;

long long gcd(long long a, long long b)
{
  if (a < b) {
    swap(a, b);
  }
  if (b == 0LL) {
    return a;
  }
  long long r;
  while ((r = a % b) != 0LL) {
    a = b;
    b = r;
  }
  return b;
}

struct ratio/*{{{*/
{
  long long n, d;
  ratio() : n(0), d(1) {}
  ratio(long long x) : n(x), d(1) {}
  ratio(long long a, long long b) : n(a), d(b)
  {
    const long long g = gcd(a, b);
    n /= g;
    d /= g;
    normalize();
  }

  void normalize()
  {
    if (d < 0) {
      n = -n;
      d = -d;
    }
  }

  bool operator==(const ratio& r) const { return n == r.n && d == r.d; }
  ratio inverse() const { return ratio(d, n); }

  ratio& operator+=(const ratio& r)
  {
    const long long g = gcd(d, r.d);
    const long long dd = d / g * r.d;
    const long long nn = r.d/g*n + d/g*r.n;
    d = dd;
    n = nn;
    normalize();
    return *this;
  }
  ratio& operator-=(const ratio& r) { return *this += ratio(-r.n, r.d); }
  ratio& operator*=(const ratio& r)
  {
    const long long g1 = gcd(n, r.d), g2 = gcd(d, r.n);
    n = (n/g1) * (r.n/g2);
    d = (d/g2) * (r.d/g1);
    normalize();
    return *this;
  }
  ratio& operator/=(const ratio& r) { return *this *= r.inverse(); }
  ratio operator+(const ratio& r) const { ratio t(*this); return t += r; }
  ratio operator-(const ratio& r) const { ratio t(*this); return t -= r; }
  ratio operator*(const ratio& r) const { ratio t(*this); return t *= r; }
  ratio operator/(const ratio& r) const { ratio t(*this); return t /= r; }
};
ostream& operator<<(ostream& os, const ratio& r)
{
  if (r.d == 1) {
    return os << r.n;
  } else {
    return os << r.n << '/' << r.d;
  }
}/*}}}*/

typedef complex<ratio> P;

inline ratio cross(const P& a, const P& b) { return a.real()*b.imag() - b.real()*a.imag(); }

struct line/*{{{*/
{
  P a, b;
  line() {}
  line(const P& p, const P& q) : a(p), b(q) {}

  inline P intersection(const line& ln) const
  {
    // assert(intersects(ln))
    const P x = b - a;
    const P y = ln.b - ln.a;
    return a + cross(y, ln.a - a)/cross(y, x)*x;
  }
};/*}}}*/

struct quad { int a, b, c, d; };

int solve(vector<P>& ps, const vector<quad>& qs)
{
  const int M = qs.size();
  for (int i = 0; i < M; i++) {
    const P p = line(ps[qs[i].a], ps[qs[i].b]).intersection(line(ps[qs[i].c], ps[qs[i].d]));
    const ratio r = p.real(), t = p.imag();
    if (r == ratio(0) && t == ratio(0)) {
      return i+1;
    }
    ps.push_back(p);
  }
  return 0;
}

int main()
{
  int N;
  cin >> N;
  vector<P> ps;
  for (int i = 0; i < N; i++) {
    long long x, y;
    cin >> x >> y;
    ps.push_back(P(x, y));
  }
  int M;
  cin >> M;
  vector<quad> qs(M);
  for (int i = 0; i < M; i++) {
    cin >> qs[i].a >> qs[i].b >> qs[i].c >> qs[i].d;
    --qs[i].a;  --qs[i].b;  --qs[i].c;  --qs[i].d;
  }
  cout << solve(ps, qs) << endl;
  return 0;
}
