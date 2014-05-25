#include <iostream>
#include <vector>
#include <set>
#include <limits>
using namespace std;

int prim(vector<vector<int> >& g)
{
  const int N = g.size();
  set<int> visited;
  visited.insert(0);
  
  int ans = 0;

  while (visited.size() < N) {
    int next_node = -1;
    int weight = -1;
    int min_cost = numeric_limits<int>::max();

    for (set<int>::const_iterator it(visited.begin()); it != visited.end(); ++it) {
      for (int i = 0; i < N; i++) {
        if (visited.find(i) == visited.end() && g[*it][i] < min_cost) {
          min_cost = g[*it][i];
          weight = g[*it][i];
          next_node = i;
        }
      }
    }
    visited.insert(next_node);
    ans += weight;
  }
  return ans;
}

int main(void)
{
  int N;
  while (cin >> N && N > 0) {
    vector<vector<int> > g(N, vector<int>(N, numeric_limits<int>::max()));

    for (int i = 0; i < N-1; i++) {
      char c;
      int k;
      cin >> c >> k;
      for (int j = 0; j < k; j++) {
        char d;
        int w;
        cin >> d >> w;
        g[c-'A'][d-'A'] = g[d-'A'][c-'A'] = w;
      }
    }
    cout << prim(g) << endl;
  }
  return 0;
}
