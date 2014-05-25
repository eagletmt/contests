#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;

struct S
{
  vector<int> parent, dist;
  S(int n) : parent(n, -1), dist(n, 0) {}
  void link(int i, int j)
  {
    parent[i] = j;
  }
  pair<int,int> query(int i)
  {
    if (parent[i] == -1) {
      return make_pair(dist[i], i);
    } else {
      const pair<int,int> r = query(parent[i]);
      if (dist[i] == 0) {
        dist[i] = r.first + abs(parent[i] - i) % 1000;
      } else {
        dist[i] += r.first;
      }
      parent[i] = r.second;
      return make_pair(dist[i], parent[i]);
    }
  }
};

int main()
{
  int T;
  scanf("%d", &T);
  while (T-- > 0) {
    int N;
    scanf("%d", &N);
    S s(N);
    char buf[4];
    while (scanf("%s", buf) != EOF && buf[0] != 'O') {
      if (buf[0] == 'E') {
        int i;
        scanf("%d", &i);
        --i;
        printf("%d\n", s.query(i).first);
      } else {
        int i, j;
        scanf("%d %d", &i, &j);
        --i;  --j;
        s.link(i, j);
      }
    }
  }
  return 0;
}
