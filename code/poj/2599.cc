#include <iostream>
#include <vector>
using namespace std;

bool dfs(const vector<vector<bool> >& g, int n, vector<bool>& visited)
{
  const int N = g.size();
  for (int i = 0; i < N; i++) {
    if (g[n][i] && !visited[i]) {
      visited[i] = true;
      if (!dfs(g, i, visited)) {
        return true;
      }
    }
  }
  return false;
}

int main()
{
  int N, K;
  cin >> N >> K;
  --K;
  vector<vector<bool> > g(N, vector<bool>(N, false));
  for (int i = 0; i < N-1; i++) {
    int a, b;
    cin >> a >> b;
    --a;  --b;
    g[a][b] = g[b][a] = true;
  }

  vector<bool> visited(N, false);
  visited[K] = true;
  for (int i = 0; i < N; i++) {
    if (g[K][i] && !visited[i]) {
      visited[i] = true;
      if (!dfs(g, i, visited)) {
        cout << "First player wins flying to airport " << i+1 << endl;
        goto FINISH;
      }
    }
  }
  cout << "First player loses" << endl;

FINISH:
  return 0;
}
