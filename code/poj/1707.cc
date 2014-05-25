#include <iostream>
#include <vector>
using namespace std;

long long gcd(long long a, long long b)
{
  if (a < b) {
    swap(a, b);
  }
  long long r;
  while ((r = a % b) != 0LL) {
    a = b;
    b = r;
  }
  return b;
}

struct ratio
{
  long long n, d;
  ratio() : n(0), d(1) {}
  ratio(long long a) : n(a), d(1) {}
  ratio(long long a, long long b) : n(a), d(b) { normalize(); }

  void normalize()
  {
    if (n == 0) {
      d = 1;
    } else {
      const long long g = gcd(n, d);
      n /= g;
      d /= g;
      if (d < 0) {
        n = -n;
        d = -d;
      }
    }
  }

  ratio inverse() const { return ratio(d, n); }

  bool operator==(const ratio& r) const { return n == r.n && d == r.d; }
  bool operator==(int x) const { return d == 1 && n == x; }
  ratio operator-() const { return ratio(-n, d); }

  ratio& operator-=(const ratio& r)
  {
    const long long dd = d * r.d;
    const long long nn = n*r.d - r.n*d;
    d = dd;
    n = nn;
    normalize();
    return *this;
  }
  ratio operator*(const ratio& r) const { return ratio(n * r.n, d * r.d); }
};
ostream& operator<<(ostream& os, const ratio& r)
{
  if (r.d == 1) {
    return os << r.n;
  } else {
    return os << r.n << '/' << r.d;
  }
}

void gaussian_elimination(vector<vector<ratio> >& a, vector<ratio>& b)
{
  const int N = a.size();
  const int M = a[0].size();
  // assert(N <= M)

  for (int i = 0, p = 0; i < M; i++, p++) {
    int q;
    for (q = p; q < N && a[q][i] == 0; q++);
    if (q == N) {
      --p;
      continue;
    }
    swap(a[i], a[q]);
    swap(b[i], b[q]);

    const ratio r = a[i][i].inverse();
    for (int k = i; k < M; k++) {
      a[i][k] = a[i][k] * r;
    }
    b[i] = b[i] * r;

    for (int j = 0; j < N; j++) {
      if (j == i) {
        continue;
      }
      const ratio t = a[j][i];
      for (int k = i; k < M; k++) {
        a[j][k] -= t * a[i][k];
      }
      b[j] -= t * b[i];
    }
  }
}

int main()
{
  static long long comb[22][22];
  for (int i = 0; i <= 21; i++) {
    comb[i][0] = comb[i][i] = 1;
  }
  for (int i = 1; i <= 21; i++) {
    for (int j = 1; j <= 21; j++) {
      comb[i][j] = comb[i-1][j] + comb[i-1][j-1];
    }
  }

  int K;
  cin >> K;
  const int N = K+1;
  vector<vector<ratio> > a(N, vector<ratio>(N));
  for (int i = 0; i < N; i++) {
    for (int j = i; j < N; j++) {
      a[i][j] = comb[j+1][i];
      if ((j-i) % 2 != 0) {
        a[i][j] = -a[i][j];
      }
    }
  }
  vector<ratio> b(N);
  b[N-1] = 1;
  gaussian_elimination(a, b);
  vector<long long> ans;
  long long lcm = 1;
  for (int i = 0; i < N; i++) {
    const long long g = gcd(lcm, b[i].d);
    lcm = (lcm * b[i].d)/g;
  }
  cout << lcm;
  for (int i = N-1; i >= 0; i--) {
    cout << " " << (b[i].n * lcm / b[i].d);
  }
  cout << " 0" << endl;
  return 0;
}
