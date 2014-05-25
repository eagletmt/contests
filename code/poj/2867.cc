#include <cstdio>
#include <vector>
using namespace std;

int main()
{
  int Ti = 0;
  int N;
  while (scanf("%d", &N) != EOF && N != 0) {
    int R;
    scanf("%d", &R);
    vector<pair<int,int> > rs(R);
    for (int i = 0; i < R; i++) {
      scanf("%d %d", &rs[i].first, &rs[i].second);
    }
    int Q;
    scanf("%d", &Q);
    printf("Genome %d\n", ++Ti);
    for (int i = 0; i < Q; i++) {
      int q;
      scanf("%d", &q);
      for (vector<pair<int,int> >::const_iterator it = rs.begin(); it != rs.end(); ++it) {
        if (it->first <= q && q <= it->second) {
          q = it->first + (it->second - q);
        }
      }
      printf("%d\n", q);
    }
  }
  return 0;
}
