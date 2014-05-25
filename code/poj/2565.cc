#include <cstdio>
#include <cmath>
using namespace std;

int main()
{
  int n;
  double d;
  scanf("%d %lf", &n, &d);

  int t;
  while (scanf("%d", &t) != EOF) {
    bool disqual = false;
    int ttl = 0;
    for (int i = 0; i < n; i++) {
      char hmmss[20];
      scanf("%s", hmmss);
      if (hmmss[0] == '-') {
        disqual = true;
      } else {
        int h = hmmss[0]-'0';
        int m = 10*(hmmss[2]-'0')+(hmmss[3]-'0');
        int s = 10*(hmmss[5]-'0')+(hmmss[6]-'0');
        ttl += 3600*h + 60*m + s;
      }
    }
    printf("%3d: ", t);
    if (disqual) {
      puts("-");
    } else {
      int s = lround(ttl / d);
      printf("%d:%02d min/km\n", s/60, s%60);
    }
  }
  return 0;
}
