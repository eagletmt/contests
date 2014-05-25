#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;

int main(void)
{
  int n;
  scanf("%d", &n);
  vector<int> seq(n);
  for (int i = 0; i < n; i++) {
    scanf("%d", &seq[i]);
  }
  sort(seq.begin(), seq.end());
  if (n % 2  == 0) {
    printf("%.1f\n", (double(seq[(n-1)/2]) + seq[(n+1)/2]) / 2.0);
  } else {
    printf("%.1f\n", double(seq[n/2]));
  }
  return 0;
}
