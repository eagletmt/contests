#include <iostream>
#include <sstream>
#include <vector>
using namespace std;

void art_visit(const vector<vector<int> >& g, int v, vector<int>& parent, vector<int>& low, vector<int>& num, int& time)/*{{{*/
{
  low[v] = num[v] = time++;
  for (vector<int>::const_iterator it = g[v].begin(); it != g[v].end(); ++it) {
    const int u = *it;
    if (num[u] == -1) {
      parent[u] = v;
      art_visit(g, u, parent, low, num, time);
      low[v] = min(low[v], low[u]);
    } else if (u != parent[v]) {
      low[v] = min(low[v], num[u]);
    }
  }
}/*}}}*/
int articulation_point(const vector<vector<int> >& g)/*{{{*/
{
  const int N = g.size();
  vector<int> num(N, -1), low(N, -1), parent(N, -1);
  int time = 0;
  art_visit(g, 0, parent, low, num, time);

  vector<int> is_art(N, false);
  for (int v = 1; v < N; v++) {
    const int u = parent[v];
    if (u == 0) {
      if (num[v] != 1) {
        is_art[0] = true;
      }
    } else {
      if (num[u] <= low[v]) {
        is_art[u] = true;
      }
    }
  }
  int ans = 0;
  for (int i = 0; i < N; i++) {
    if (is_art[i]) {
      ++ans;
    }
  }
  return ans;
}/*}}}*/

int main()
{
  ios::sync_with_stdio(false);
  int N;
  while (cin >> N && N != 0) {
    vector<vector<int> > g(N);
    cin.ignore();
    string line;
    while (getline(cin, line) && line != "0") {
      istringstream iss(line);
      int u;
      iss >> u;
      --u;
      for (int v; iss >> v;) {
        --v;
        g[u].push_back(v);
        g[v].push_back(u);
      }
    }
    cout << articulation_point(g) << endl;
  }
}
