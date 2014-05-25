#include <iostream>
#include <vector>
#include <complex>
using namespace std;
typedef complex<long long> P;

inline P::value_type cross(const P& a, const P& b) { return a.real()*b.imag() - b.real()*a.imag(); }

bool ok(const vector<P>& ps, int N, int i1, int i2)
{
  const int NM = ps.size();
  const int color = i1 < N;
  int cnt[2][2] = {{0, 0}, {0, 0}};
  for (int i = 0; i < NM; i++) {
    const long long c = cross(ps[i2] - ps[i1], ps[i] - ps[i1]);
    const int col = i < N;
    if (c == 0) {
      if (color != col) {
        return false;
      }
    } else {
      ++cnt[col][c < 0];
    }
  }
  return (cnt[0][0] == 0 && cnt[1][1] == 0) || (cnt[0][1] == 0 && cnt[1][0] == 0);
}

bool check(const vector<P>& ps, int N)
{
  for (int i = 0; i < N; i++) {
    for (int j = i+1; j < N; j++) {
      if (ok(ps, N, i, j)) {
        return true;
      }
    }
  }
  const int NM = ps.size();
  for (int i = N; i < NM; i++) {
    for (int j = i+1; j < NM; j++) {
      if (ok(ps, N, i, j)) {
        return true;
      }
    }
  }
  return false;
}

inline int cmp(long long x, long long y)
{
  if (x == y) {
    return 0;
  } else if (x < y) {
    return -1;
  } else {
    return 1;
  }
}

bool check_edgecase(const vector<P>& ps, const int N)
{
  const int NM = ps.size();
  const int x = cmp(ps[0].real(), ps[N].real());
  for (int i = 0; i < N; i++) {
    for (int j = N; j < NM; j++) {
      if (x != cmp(ps[i].real(), ps[j].real())) {
        return false;
      }
    }
  }
  const int y = cmp(ps[0].imag(), ps[N].imag());
  for (int i = 0; i < N; i++) {
    for (int j = N; j < NM; j++) {
      if (y != cmp(ps[i].imag(), ps[j].imag())) {
        return false;
      }
    }
  }
  return true;
}

int main()
{
  int N, M;
  while (cin >> N >> M && N != 0) {
    vector<P> ps(N+M);
    for (int i = 0; i < N+M; i++) {
      cin >> ps[i].real() >> ps[i].imag();
    }

    bool straight = true;
    if (N+M > 2) {
      const long long c0 = cross(ps[2]-ps[0], ps[1]-ps[0]);
      for (int i = 3; i < N+M; i++) {
        const long long c = cross(ps[i]-ps[0], ps[1]-ps[0]);
        if (c != c0) {
          straight = false;
          break;
        }
      }
    }
    if (straight) {
      cout << (check_edgecase(ps, N) ? "YES" : "NO") << endl;
    } else {
      cout << (check(ps, N) ? "YES" : "NO") << endl;
    }
  }
  return 0;
}
