#include <cstdio>
#include <algorithm>
using namespace std;

int main()
{
  int N;
  while (scanf("%d", &N) != EOF && N != 0) {
    static int dist[200][200];
    for (int i = 0; i < N; i++) {
      fill_n(dist[i], N, 0);
    }
    for (int u, v; scanf("%d %d", &u, &v) != EOF && u != 0;) {
      --u;  --v;
      char buf[32];
      scanf("%s", buf);
      for (int i = 0; buf[i]; i++) {
        dist[u][v] |= 1 << (buf[i] - 'a');
      }
    }

    for (int k = 0; k < N; k++) {
      for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
          dist[i][j] |= dist[i][k] & dist[k][j];
        }
      }
    }

    for (int u, v; scanf("%d %d", &u, &v) != EOF && u != 0;) {
      --u;  --v;
      bool found = false;
      for (int i = 0; i < 26; i++) {
        if (dist[u][v] & (1<<i)) {
          found = true;
          putchar(i+'a');
        }
      }
      if (!found) {
        putchar('-');
      }
      putchar('\n');
    }
    putchar('\n');
  }
  return 0;
}
