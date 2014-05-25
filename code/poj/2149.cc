#include <iostream>
#include <vector>
#include <algorithm>
#include <complex>
#include <cmath>
#include <iterator>
using namespace std;
typedef complex<double> P;
static const double EPS = 1e-6;

struct P3
{
  double x, y, z;
  P3() {}
  P3(double a, double b, double c) : x(a), y(b), z(c) {}
  P3& operator+=(const P3& q) { x += q.x; y += q.y; z += q.z; return *this; }
  P3& operator-=(const P3& q) { x -= q.x; y -= q.y; z -= q.z; return *this; }
  P3& operator*=(double a) { x *= a; y *= a; z *= a; return *this; }
};
P3 operator+(const P3& p, const P3& q) { P3 r(p); return r += q; }
P3 operator-(const P3& p, const P3& q) { P3 r(p); return r -= q; }
P3 operator*(const P3& p, double a) { P3 q(p); q *= a; return q; }
P3 operator*(double a, const P3& p) { return p*a; }
inline double dot(const P3& p, const P3& q) { return p.x*q.x + p.y*q.y + p.z*q.z; }
inline double abs(const P3& p) { return sqrt(dot(p, p)); }

struct circle
{
  P o;
  double r;
  circle() {}
  circle(const P& p, double x) : o(p), r(x) {}

  inline bool contains(const circle& c) const { return abs(o - c.o)+c.r <= r; }
  inline bool intersects(const circle& c) const { return !contains(c) && !c.contains(*this) && abs(o - c.o) <= r + c.r; }
  pair<P,P> intersection(const circle& c) const
  {
    // assert(intersects(c))
    const double d = abs(o - c.o);
    const double cos_ = (d*d + r*r - c.r*c.r) / (2*d);
    const double sin_ = sqrt(r*r - cos_*cos_);
    const P e = (c.o - o) / d;
    return make_pair(o + e*P(cos_, sin_), o + e*P(cos_, -sin_));
  }
};

struct sphere
{
  P3 o;
  double r;
  sphere(const P3& p, double x) : o(p), r(x) {}

  inline circle cutz(double z) const { return circle(P(o.x, o.y), sqrt(r*r - (z-o.z)*(z-o.z))); }
  inline bool contains(const sphere& s) const { return abs(o - s.o)+s.r <= r; }
  inline bool intersects(const sphere& s) const { return !contains(s) && !s.contains(*this) && abs(o - s.o) <= r + s.r; }

  double center_z(const sphere& s) const
  {
    const P3 p = s.o - o;
    const double L = abs(p);
    const double x1 = (r*r - s.r*s.r + L*L)/(2*L);
    return (o + x1/L*p).z;
  }

  pair<double,double> intersection_z(const sphere& that) const
  {
    const double z0 = center_z(that);
    double left = z0, right = min(o.z+r, that.o.z+that.r);
    for (int i = 0; i < 100; i++) {
      const double mid = (left+right)/2.0;
      const circle c1 = cutz(mid), c2 = that.cutz(mid);
      const double d = abs(c1.o - c2.o);
      if (d < c1.r + c2.r) {
        left = mid;
      } else {
        right = mid;
      }
    }
    const double z1 = (left+right)/2.0;

    left = max(o.z-r, that.o.z-that.r), right = z0;
    for (int i = 0; i < 100; i++) {
      const double mid = (left+right)/2.0;
      const circle c1 = cutz(mid), c2 = that.cutz(mid);
      const double d = abs(c1.o - c2.o);
      if (d < c1.r + c2.r) {
        right = mid;
      } else {
        left = mid;
      }
    }
    const double z2 = (left+right)/2.0;
    return make_pair(z1, z2);
  }
};

struct DisjointSet/*{{{*/
{
  vector<int> parent;

  int root(int x)
  {
    if (parent[x] < 0) {
      return x;
    } else {
      parent[x] = root(parent[x]);
      return parent[x];
    }
  }

  explicit DisjointSet(int n) : parent(n, -1) {}

  bool unite(int x, int y)
  {
    const int a = root(x);
    const int b = root(y);
    if (a != b) {
      if (parent[a] < parent[b]) {
        parent[a] += parent[b];
        parent[b] = a;
      } else {
        parent[b] += parent[a];
        parent[a] = b;
      }
      return true;
    } else {
      return false;
    }
  }

  bool find(int x, int y) { return root(x) == root(y); }
  int size(int x) { return -parent[root(x)]; }
};/*}}}*/

int count_sphere(const vector<sphere>& ss, double z)
{
  vector<circle> cs;
  for (vector<sphere>::const_iterator it = ss.begin(); it != ss.end(); ++it) {
    if (abs(z - it->o.z) < it->r) {
      cs.push_back(it->cutz(z));
    }
  }

  const int N = cs.size();
  DisjointSet s(N);
  for (int i = 0; i < N; i++) {
    for (int j = i+1; j < N; j++) {
      if (cs[i].contains(cs[j]) || cs[j].contains(cs[i]) || cs[i].intersects(cs[j])) {
        s.unite(i, j);
      }
    }
  }
  int ans = 0;
  for (int i = 0; i < N; i++) {
    if (s.parent[i] < 0) {
      ++ans;
    }
  }
  return ans;
}

int main()
{
  int N;
  while (cin >> N && N != 0) {
    vector<sphere> ss;
    vector<double> zs;
    for (int i = 0; i < N; i++) {
      int x, y, z, r;
      cin >> x >> y >> z >> r;
      ss.push_back(sphere(P3(x, y, z), r));
      zs.push_back(z-r);
      zs.push_back(z+r);
    }

    for (vector<sphere>::const_iterator it = ss.begin(); it != ss.end(); ++it) {
      for (vector<sphere>::const_iterator jt = it+1; jt != ss.end(); ++jt) {
        if (it->intersects(*jt)) {
          const pair<double,double> r = it->intersection_z(*jt);
          zs.push_back(r.first);
          zs.push_back(r.second);
        }
      }
    }
    sort(zs.begin(), zs.end());

    vector<char> ans;
    int prev = 0;
    for (vector<double>::const_iterator it = zs.begin(); it != zs.end(); ++it) {
      const int r = count_sphere(ss, *it+EPS);
      if (prev < r) {
        ans.push_back('1');
      } else if (prev > r) {
        ans.push_back('0');
      }
      prev = r;
    }

    cout << ans.size() << endl;
    copy(ans.begin(), ans.end(), ostream_iterator<char>(cout, ""));
    cout << endl;
  }
  return 0;
}
