#include <iostream>
#include <sstream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

void show(const vector<int> *g, int n)
{
  cout << '(' << n+1;
  for (vector<int>::const_iterator it = g[n].begin(); it != g[n].end(); ++it) {
    cout << ' ';
    show(g, *it);
  }
  cout << ')';
}

int main()
{
  for (string line; getline(cin, line);) {
    if (line.empty()) {
      cout << "(1)" << endl;
      continue;
    }
    istringstream iss(line);
    vector<int> v;
    for (int n; iss >> n;) {
      v.push_back(n-1);
    }
    static vector<int> g[50];
    for (int i = 0; i < 50; i++) {
      g[i].clear();
    }
    int children[50];
    fill_n(children, 50, 0);
    for (vector<int>::const_iterator it = v.begin(); it != v.end(); ++it) {
      ++children[*it];
    }

    priority_queue<int> q;
    for (int i = 0; i < 50; i++) {
      if (children[i] == 0) {
        q.push(-i);
      }
    }
    for (vector<int>::const_iterator it = v.begin(); it != v.end(); ++it) {
      const int n = -q.top();
      q.pop();
      g[*it].push_back(n);
      --children[*it];
      if (children[*it] == 0) {
        q.push(-*it);
      }
    }
    show(g, v.back());
    cout << endl;
  }
  return 0;
}
