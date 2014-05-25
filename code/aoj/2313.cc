#include <iostream>
#include <vector>
#include <queue>
using namespace std;

bool augment(vector<vector<int> >& flow, const vector<vector<int> >& capacity, int s, int g)
{
  int size = capacity.size();
  queue<int> q;
  vector<int> prev(size, -1);
  prev[s] = s;
  q.push(s);
  while (!q.empty()) {
    int n = q.front();
    q.pop();
    for (int i = 0; i < size; i++) {
      if (capacity[n][i] - flow[n][i] <= 0) continue;
      if (prev[i] != -1) continue;
      prev[i] = n;
      q.push(i);
      if (i == g) goto endloop;
    }
  }
endloop:
  if (prev[g] == -1) return false;
  for (int i = g; prev[i] != i; i = prev[i]) {
    ++flow[prev[i]][i];
    --flow[i][prev[i]];
  }
  return true;
}

pair<int, vector<vector<int> > >
maxflow(const vector<vector<int> >& capacity, int s, int g) {
  int size = capacity.size();
  vector<vector<int> > flow(size, vector<int>(size, 0));
  int ans = 0;
  while (augment(flow, capacity, s, g)) {
    ++ans;
  }
  return make_pair(ans, flow);
}

void bfs(vector<vector<int> >& flow, int start, int goal)
{
  const int N = flow.size();
  queue<int> q;
  vector<int> prev(N, -1);
  q.push(start);
  prev[start] = start;
  while (!q.empty()) {
    int n = q.front();
    q.pop();
    if (n == goal) {
      while (prev[n] != n) {
        flow[prev[n]][n] = flow[n][prev[n]] = 0;
        n = prev[n];
      }
      return;
    }
    for (int i = 0; i < N; i++) {
      if (flow[n][i] > 0 && prev[i] == -1) {
        prev[i] = n;
        q.push(i);
      }
    }
  }
}

int main()
{
  int N, E, Q;
  cin >> N >> E >> Q;
  vector<vector<int> > capacity(N, vector<int>(N, 0));
  for (int i = 0; i < E; i++) {
    int f, t;
    cin >> f >> t;
    --f;    --t;
    capacity[f][t] = capacity[t][f] = 1;
  }

  pair<int, vector<vector<int> > > r = maxflow(capacity, 0, N-1);
  int maxf = r.first;
  vector<vector<int> > flow = r.second;
  while (Q-- > 0) {
    int m, a, b;
    cin >> m >> a >> b;
    --a;    --b;
    if (m == 1) {
      capacity[a][b] = capacity[b][a] = 1;
    } else {
      capacity[a][b] = capacity[b][a] = 0;
      if (flow[a][b] != 0) {
        --maxf;
        if (flow[a][b] < 0) {
          swap(a, b);
        }
        flow[a][b] = flow[b][a] = 0;
        bfs(flow, 0, a);
        bfs(flow, b, N-1);
      }
    }
    if (augment(flow, capacity, 0, N-1)) {
      ++maxf;
    }

    cout << maxf << endl;
  }
  return 0;
}
