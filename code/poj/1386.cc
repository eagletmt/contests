#include <cstdio>
#include <cstring>
#include <vector>
using namespace std;

struct DisjointSet/*{{{*/
{
  vector<int> parent;

  int root(int x)
  {
    if (parent[x] < 0) {
      return x;
    } else {
      parent[x] = root(parent[x]);
      return parent[x];
    }
  }

  explicit DisjointSet(int n) : parent(n, -1) {}

  bool unite(int x, int y)
  {
    const int a = root(x);
    const int b = root(y);
    if (a != b) {
      if (parent[a] < parent[b]) {
        parent[a] += parent[b];
        parent[b] = a;
      } else {
        parent[b] += parent[a];
        parent[a] = b;
      }
      return true;
    } else {
      return false;
    }
  }

  bool find(int x, int y) { return root(x) == root(y); }
  int size(int x) { return -parent[root(x)]; }
};/*}}}*/

int main()
{
  int T;
  scanf("%d", &T);
  while (T-- > 0) {
    int N;
    scanf("%d", &N);
    vector<int> beg(26, 0), end(26, 0);
    DisjointSet s(26);
    int c;
    for (int i = 0; i < N; i++) {
      char buf[1001];
      scanf("%s", buf);
      const int b = buf[0]-'a', e = buf[strlen(buf)-1]-'a';
      ++beg[b];
      ++end[e];
      s.unite(b, e);
      c = b;
    }

    bool connected = true;
    for (int i = 0; i < 26; i++) {
      if ((beg[i] || end[i]) && !s.find(c, i)) {
        connected = false;
        break;
      }
    }
    if (!connected) {
      puts("The door cannot be opened.");
      continue;
    }

    int b = 0, e = 0;
    for (int i = 0; i < 26; i++) {
      if (beg[i] > end[i]) {
        b += beg[i] - end[i];
      } else if (beg[i] < end[i]) {
        e += end[i] - beg[i];
      }
    }
    if (b < 2 && e < 2) {
      puts("Ordering is possible.");
    } else {
      puts("The door cannot be opened.");
    }
  }
  return 0;
}
