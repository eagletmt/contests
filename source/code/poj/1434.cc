#include <cstdio>
#include <algorithm>
using namespace std;

struct cistern { int b, h, s; };

double volume(const cistern *v, int N, double h)
{
  double vol = 0.0;
  for (int i = 0; i < N; i++) {
    if (v[i].b < h) {
      vol += v[i].s * (min(double(v[i].b + v[i].h), h) - v[i].b);
    }
  }
  return vol;
}

int main()
{
  int T;
  scanf("%d", &T);
  while (T-- > 0) {
    int N;
    scanf("%d", &N);
    static cistern v[50000];
    int ttl = 0;
    double left = 1e10, right = 0.0;
    for (int i = 0; i < N; i++) {
      int w, d;
      scanf("%d %d %d %d", &v[i].b, &v[i].h, &w, &d);
      v[i].s = w*d;
      ttl += v[i].s*v[i].h;
      left = min(left, double(v[i].b));
      right = max(right, double(v[i].b + v[i].h));
    }
    int V;
    scanf("%d", &V);
    if (V > ttl) {
      puts("OVERFLOW");
    } else {
      for (int i = 0; i < 100; i++) {
        const double mid = (left + right)/2.0;
        if (volume(v, N, mid) < V) {
          left = mid;
        } else {
          right = mid;
        }
      }
      printf("%.2f\n", (left + right)/2.0);
    }
  }
  return 0;
}
