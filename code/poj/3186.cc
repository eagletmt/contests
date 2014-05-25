#include <cstdio>
#include <algorithm>
using namespace std;

int N;
int v[2000];

int memo[2000][2000];
int solve(int beg, int end)
{
  int& ans = memo[beg][end];
  if (ans) {
    return ans;
  }
  const int age = N - (end - beg);
  if (beg == end) {
    return ans = v[beg] * age;
  } else {
    return ans = max(v[beg] * age + solve(beg+1, end), v[end] * age + solve(beg, end-1));
  }
}

int main()
{
  scanf("%d", &N);
  for (int i = 0; i < N; i++) {
    scanf("%d", &v[i]);
  }
  printf("%d\n", solve(0, N-1));
  return 0;
}
