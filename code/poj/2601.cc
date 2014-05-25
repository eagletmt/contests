#include <cstdio>
using namespace std;

int main()
{
  int n;
  double a0, an1;
  scanf("%d %lf %lf", &n, &a0, &an1);
  double c_sum = 0.0;
  for (int i = 0; i < n; i++) {
    double c;
    scanf("%lf", &c);
    c_sum += (n-i) * c;
  }
  printf("%.2f\n", (an1 + n*a0 - 2*c_sum)/(n+1));
  return 0;
}

