#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <queue>
using namespace std;

pair<vector<int>, vector<int> > read(int N)
{
  vector<int> v[2];
  for (int i = 0; i < 2; i++) {
    v[i].resize(N);
    for (int j = 0; j < N; j++) {
      cin >> v[i][j];
    }
  }
  return make_pair(v[0], v[1]);
}

int main()
{
  int N;
  for (int Ti = 1; cin >> N && N != 0; Ti++) {
    vector<int> v[2];
    for (int i = 0; i < 2; i++) {
      v[i].resize(N);
      for (int j = 0; j < N; j++) {
        cin >> v[i][j];
      }
    }
    map<vector<int>, vector<vector<int> > > g;
    for (int n; cin >> n && n != -1;) {
      vector<int> a(N), b(N);
      a[0] = n;
      for (int i = 1; i < N; i++) {
        cin >> a[i];
      }
      for (int i = 0; i < N; i++) {
        cin >> b[i];
      }
      g[a].push_back(b);
      g[b].push_back(a);
    }

    cout << "Maze #" << Ti << " ";
    queue<vector<int> > q;
    set<vector<int> > visited;
    q.push(v[0]);
    visited.insert(v[0]);
    while (!q.empty()) {
      const vector<int> n = q.front();
      q.pop();
      if (n == v[1]) {
        cout << "can";
        goto OK;
      }
      vector<vector<int> >& es = g[n];
      for (vector<vector<int> >::const_iterator it = es.begin(); it != es.end(); ++it) {
        if (!visited.count(*it)) {
          visited.insert(*it);
          q.push(*it);
        }
      }
    }
    cout << "cannot";
OK:
    cout << " be travelled" << endl;
  }
  return 0;
}
