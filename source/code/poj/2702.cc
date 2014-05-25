#include <cstdio>
#include <vector>
#include <queue>
#include <map>
#include <algorithm>
using namespace std;

typedef vector<multimap<char,int> > graph;
typedef multimap<char,int>::const_iterator Iterator;

pair<int,graph> read()
{
  int S, E, I;
  scanf("%d %d %d", &S, &E, &I);
  --I;
  graph g(S);
  for (int i = 0; i < E; i++) {
    int u, v;
    char c;
    scanf("%d %c %d", &u, &c, &v);
    --u;  --v;
    g[u].insert(make_pair(c, v));
  }
  return make_pair(I, g);
}

bool solve(int prog_start, const graph& prog, int req_start, const graph& req)
{
  vector<vector<int> > visited(prog.size(), vector<int>(req.size(), false));
  visited[prog_start][req_start] = true;
  queue<pair<int,int> > q;
  q.push(make_pair(prog_start, req_start));
  while (!q.empty()) {
    const int i = q.front().first;
    const int j = q.front().second;
    q.pop();

    for (multimap<char,int>::const_iterator it = prog[i].begin(); it != prog[i].end(); ++it) {
      const int k = it->second;
      pair<Iterator, Iterator> r = req[j].equal_range(it->first);
      if (r.first == r.second) {
        // nothing in common
        if (!visited[k][j]) {
          visited[k][j] = true;
          q.push(make_pair(k, j));
        }
      } else {
        while (r.first != r.second) {
          const int l = r.first->second;
          if (l < 0) {
            return false;
          }
          if (!visited[k][l]) {
            visited[k][l] = true;
            q.push(make_pair(k, l));
          }
          ++r.first;
        }
      }
    }
  }
  return true;
}

int main()
{
  int T;
  scanf("%d", &T);
  while (T-- > 0) {
    const pair<int,graph> prog = read();
    const pair<int,graph> req = read();
    puts(solve(prog.first, prog.second, req.first, req.second) ? "satisfied" : "violated");
  }
  return 0;
}
