#include <cstdio>
#include <algorithm>
using namespace std;
static const double EPS = 1e-6;

struct quest { int a, b, s; };

double simulate(const quest *v, int N, int XP)
{
  double p = 1.0;
  for (int i = 0; i < N; i++) {
    if (XP < v[i].a) {
      return 0.0;
    } else if (v[i].a <= XP && XP < v[i].b) {
      p *= double(XP - v[i].a)/double(v[i].b - v[i].a);
      XP += v[i].s;
    } else {
      XP += v[i].s;
    }
  }
  return p;
}

int main()
{
  int N, D;
  scanf("%d %d", &N, &D);
  quest v[10];
  int a[10];
  for (int i = 0; i < N; i++) {
    a[i] = i;
    scanf("%d %d %d", &v[i].a, &v[i].b, &v[i].s);
  }

  quest w[10];
  double ans = -1;
  int perm[10];
  do {
    for (int i = 0; i < N; i++) {
      w[i] = v[a[i]];
    }
    const double x = simulate(w, N, D);
    if (x+EPS > ans) {
      ans = x;
      copy(a, a+N, perm);
    }
  } while (next_permutation(a, a+N));

  printf("%.3f\n", ans);
  for (int i = 0; i < N; i++) {
    if (i != 0) {
      putchar(' ');
    }
    printf("%d", perm[i]+1);
  }
  putchar('\n');
  return 0;
}
