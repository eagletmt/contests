#include <cstdio>
#include <vector>
#include <algorithm>
#include <cmath>
using namespace std;
static const double EPS = 1e-6;

struct P
{
  double x, y, z;

  inline double dot(const P& a) const
  {
    return x*a.x + y*a.y + z*a.z;
  }

  inline double norm() const
  {
    return sqrt(dot(*this));
  }

  inline double angle(const P& a) const
  {
    return acos(dot(a) / (norm() * a.norm()));
  }
};

struct observable
{
  typedef vector<pair<P,double> >::const_iterator iter;
  iter first, last;
  observable(const iter& f, const iter& l) : first(f), last(l) {}
  bool operator()(const P& p) const
  {
    for (iter it = first; it != last; ++it) {
      if (p.angle(it->first) < it->second + EPS) {
        return true;
      }
    }
    return false;
  }
};

int main()
{
  int N;
  while (scanf("%d", &N) != EOF && N != 0) {
    vector<P> ps(N);
    for (int i = 0; i < N; i++) {
      scanf("%lf %lf %lf", &ps[i].x, &ps[i].y, &ps[i].z);
    }
    int M;
    scanf("%d", &M);
    vector<pair<P,double> > qs(M);
    for (int i = 0; i < M; i++) {
      scanf("%lf %lf %lf %lf", &qs[i].first.x, &qs[i].first.y, &qs[i].first.z, &qs[i].second);
    }
    printf("%ld\n", count_if(ps.begin(), ps.end(), observable(qs.begin(), qs.end())));
  }
  return 0;
}
