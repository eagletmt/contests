#include <cstdio>
#include <bitset>
using namespace std;

int M, N;
static const int MAXM = 300;
bitset<MAXM> a[16];

bool dfs(const bitset<MAXM>& s, unsigned used, int from)
{
  if (s.count() == N) {
    return true;
  }
  for (int i = from; i < M; i++) {
    if (!(used & (1<<i)) && (s & a[i]) == 0) {
      if (dfs(s | a[i], used | (1<<i), i+1)) {
        return true;
      }
    }
  }
  return false;
}

int main()
{
  while (scanf("%d %d", &M, &N) != EOF) {
    for (int i = 0; i < M; i++) {
      a[i].reset();
      for (int j = 0; j < N; j++) {
        int x;
        scanf("%d", &x);
        a[i].set(j, x != 0);
      }
    }

    puts(dfs(0, 0, 0) ?  "Yes, I found it" : "It is impossible");
  }
  return 0;
}
