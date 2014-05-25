#include <cstdio>
#include <vector>
using namespace std;

int main()
{
  int N;
  while (scanf("%d", &N) != EOF) {
    int M;
    scanf("%d", &M);
    vector<int> req(M);
    for (int i = 0; i < M; i++) {
      scanf("%d", &req[i]);
      --req[i];
    }

    vector<int> removed;
    vector<int> bin(N, 0);
    int policy = 1;
    for (char cmd; scanf("%c", &cmd) != EOF && cmd != 'e';) {
      switch (cmd) {
        case 'a':
          {
            int x;
            scanf("%d", &x);
            ++bin[x-1];
          }
          break;
        case 'r':
          {
            int p = -1;
            if (policy == 1) {
              for (int i = 0; i < N; i++) {
                if (bin[i] > 0) {
                  p = i;
                  --bin[i];
                  break;
                }
              }
            } else {
              for (int i = N-1; i >= 0; i--) {
                if (bin[i] > 0) {
                  p = i;
                  --bin[i];
                  break;
                }
              }
            }
            removed.push_back(p);
          }
          break;
        case 'p':
          scanf("%d", &policy);
          break;
      }
    }
    for (int i = 0; i < M; i++) {
      printf("%d\n", removed[req[i]]+1);
    }
    puts("");
  }
  return 0;
}
