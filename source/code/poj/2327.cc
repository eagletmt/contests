#include <cstdio>
#include <vector>
using namespace std;

int main()
{
  int N;
  while (scanf("%d", &N) != EOF && N != 0) {
    double Pl, Pr;
    scanf("%lf %lf", &Pl, &Pr);

    vector<double> dp(N+1, 1e10);
    dp[0] = 0;
    for (int i = 1; i <= N; i++) {
      for (int j = 0; j < i; j++) {
        const double El = dp[j], Er = dp[i-j-1];
        const double x = (1 + Pl*El + Pr*Er)/(1 - Pl - Pr);
        dp[i] = min(dp[i], El + Er + x);
      }
    }
    printf("%.2f\n", dp[N]);
  }
  return 0;
}
