#include <iostream>
#include <vector>
#include <queue>
using namespace std;

struct triple
{
  int i, j, k;
  triple() {}
  triple(int a, int b, int c) : i(a), j(b), k(c) {}
  bool operator==(const triple& that) const { return i == that.i && j == that.j && k == that.k; }
};

int bfs(const vector<vector<string> >& cube, const triple& start, const triple& goal)
{
  const int N = cube.size();
  queue<triple> q;
  vector<vector<vector<int> > > dist(N, vector<vector<int> >(N, vector<int>(N, 1000000)));
  dist[start.i][start.j][start.k] = 0;
  q.push(start);
  while (!q.empty()) {
    const triple t = q.front();
    q.pop();
    if (t == goal) {
      return dist[t.i][t.j][t.k];
    }
    for (int d = 0; d < 6; d++) {
      static const int di[] = {-1, 1, 0, 0, 0, 0};
      static const int dj[] = {0, 0, -1, 1, 0, 0};
      static const int dk[] = {0, 0, 0, 0, -1, 1};
      const int i = t.i + di[d];
      const int j = t.j + dj[d];
      const int k = t.k + dk[d];
      if (0 <= i && i < N && 0 <= j && j < N && 0 <= k && k < N && cube[i][j][k] == 'O' && dist[t.i][t.j][t.k]+1 < dist[i][j][k]) {
        dist[i][j][k] = dist[t.i][t.j][t.k] + 1;
        q.push(triple(i, j, k));
      }
    }
  }
  return -1;
}

int main()
{
  string word;
  int N;
  while (cin >> word >> N) {
    vector<vector<string> > cube(N, vector<string>(N));
    for (int i = 0; i < N; i++) {
      for (int j = 0; j < N; j++) {
        cin >> cube[i][j];
      }
    }
    triple start, goal;
    cin >> start.k >> start.j >> start.i;
    cin >> goal.k >> goal.j >> goal.i;
    cin >> word;
    const int r = bfs(cube, start, goal);
    if (r == -1) {
      cout << "NO ROUTE" << endl;
    } else {
      cout << N << ' ' << r << endl;
    }
  }
  return 0;
}
