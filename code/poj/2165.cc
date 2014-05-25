#include <cstdio>
#include <vector>
using namespace std;
static const double EPS = 1e-8;

struct P3 { double x, y, z; };

struct window
{
  int ps[4], z;
  int x1() const { return ps[0]; }
  int y1() const { return ps[1]; }
  int x2() const { return ps[2]; }
  int y2() const { return ps[3]; }
};

bool check(const vector<window>& v, int x1, int y1, int z1, int x2, int z2, double& a, vector<P3>& ans)
{
  const double dx = double(x2 - x1)/double(z2 - z1);
  a = x1 + dx*(-z1);
  double dy = double(y1 - 0)/double(z1);
  const int N = v.size();
  for (int i = 0; i < N; i++) {
    const double x = a + dx*(v[i].z);
    const double y = 0 + dy*(v[i].z);
    ans[i].x = x;
    ans[i].y = y;
    ans[i].z = v[i].z;
    if (x < v[i].x1() - EPS || v[i].x2() < x - EPS || y < v[i].y1() - EPS || v[i].y2() < y - EPS) {
      return false;
    }
  }
  return true;
}

int main()
{
  int N;
  scanf("%d", &N);
  vector<window> v(N);
  for (int i = 0; i < N; i++) {
    scanf("%d %d %d %d %d", &v[i].ps[0], &v[i].ps[1], &v[i].ps[2], &v[i].ps[3], &v[i].z);
  }

  vector<P3> ans(N);
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < 4; j++) {
      static const int tbl[4][2] = {
        {0, 1}, {0, 3}, {2, 1}, {2, 3},
      };
      const int x1 = v[i].ps[tbl[j][0]], y1 = v[i].ps[tbl[j][1]], z1 = v[i].z;
      for (int k = 0; k < N; k++) {
        if (i == k) {
          continue;
        }
        for (int l = 0; l < 2; l++) {
          double x;
          if (check(v, x1, y1, z1, v[k].ps[2*l], v[k].z, x, ans)) {
            puts("SOLUTION");
            printf("%.6f\n", x);
            for (vector<P3>::const_iterator it = ans.begin(); it != ans.end(); ++it) {
              printf("%.6f %.6f %.6f\n", it->x, it->y, it->z);
            }
            return 0;
          }
        }
      }
    }
  }
  puts("UNSOLVABLE");
  return 0;
}
