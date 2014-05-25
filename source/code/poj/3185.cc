#include <iostream>
#include <queue>
#include <algorithm>
using namespace std;

int main()
{
  unsigned init = 0;
  for (int i = 0; i < 20; i++) {
    int x;
    cin >> x;
    init |= x << i;
  }
  static int dist[1<<20];
  fill_n(dist, 1<<20, 10000000);
  dist[init] = 0;
  queue<unsigned> q;
  q.push(init);
  while (!q.empty() && q.front() != 0) {
    unsigned s = q.front();
    q.pop();
    for (int i = 0; i < 20; i++) {
      unsigned t;
      if (i == 0) {
        t = s ^ 3;
      } else if (i == 19) {
        t = s ^ (3 << 18);
      } else {
        t = s ^ (7 << (i-1));
      }
      if (dist[s]+1 < dist[t]) {
        dist[t] = dist[s]+1;
        q.push(t);
      }
    }
  }
  cout << dist[0] << endl;
  return 0;
}
