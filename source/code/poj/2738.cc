#include <cstdio>
#include <vector>
using namespace std;

int cache[1000][1000];
bool is_cached[1000][1000];
int solve(const vector<int>& v, int begin, int end)
{
  if (begin > end) {
    return 0;
  } else if (is_cached[begin][end]) {
    return cache[begin][end];
  } else {
    const int l = v[begin+1] >= v[end]
      ? solve(v, begin+2, end) + v[begin] - v[begin+1]
      : (solve(v, begin+1, end-1) + v[begin] - v[end]);
    const int r = v[begin] >= v[end-1]
      ? solve(v, begin+1, end-1) + v[end] - v[begin]
      : (solve(v, begin, end-2) + v[end] - v[end-1]);
    is_cached[begin][end] = true;
    return cache[begin][end] = max(l, r);
  }
}

int main()
{
  int T = 0;
  int N;
  while (scanf("%d", &N) != EOF && N != 0) {
    vector<int> v(N);
    for (int i = 0; i < N; i++) {
      scanf("%d", &v[i]);
    }
    for (int i = 0; i < N; i++) {
      fill_n(is_cached[i], N, false);
    }
    printf("In game %d, the greedy strategy might lose by as many as %d points.\n", ++T, solve(v, 0, N-1));
  }
  return 0;
}
