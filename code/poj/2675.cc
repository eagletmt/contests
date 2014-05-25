#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;

struct song
{
  int id, l;
  double f;
  bool operator<(const song& s) const { return s.f*l < f*s.l; }
};

int main()
{
  for (int N; scanf("%d", &N) != EOF;) {
    vector<song> v(N);
    for (int i = 0; i < N; i++) {
      scanf("%d %d %lf", &v[i].id, &v[i].l, &v[i].f);
    }
    int S;
    scanf("%d", &S);
    sort(v.begin(), v.end());
    printf("%d\n", v[S-1].id);
  }
  return 0;
}
