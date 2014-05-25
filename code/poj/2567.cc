#include <iostream>
#include <algorithm>
using namespace std;

typedef string::const_iterator Iterator;

int number(Iterator& it, const Iterator& last)
{
  int n = 0;
  while (it != last && '0' <= *it && *it <= '9') {
    n = 10*n + *it-'0';
    ++it;
  }
  return n-1;
}

int parse(bool g[50][50], Iterator& it, const Iterator& last)
{
  if (*it != '(') {
    throw "e";
  }
  ++it;
  int u = number(it, last);
  while (*it == '(') {
    int v = parse(g, it, last);
    g[u][v] = g[v][u] = true;
  }
  if (*it != ')') {
    throw "f";
  }
  ++it;
  return u;
}

int main()
{
  for (string line; getline(cin, line);) {
    bool g[50][50];
    for (int i = 0; i < 50; i++) {
      fill_n(g[i], 50, 0);
    }
    line.erase(remove(line.begin(), line.end(), ' '), line.end());
    Iterator it = line.begin(), last = line.end();
    parse(g, it, last);

    int deg[50];
    fill_n(deg, 50, 0);
    for (int i = 0; i < 50; i++) {
      for (int j = 0; j < 50; j++) {
        if (g[i][j]) {
          ++deg[j];
        }
      }
    }
    for (int t = 0; t < 50; t++) {
      for (int i = 0; i < 50; i++) {
        if (deg[i] == 1) {
          --deg[i];
          for (int j = 0; j < 50; j++) {
            if (g[i][j]) {
              g[i][j] = g[j][i] = false;
              --deg[j];
              if (t != 0) {
                cout << " ";
              }
              cout << j+1;
              goto NEXT;
            }
          }
        }
      }
NEXT:
      ;
    }
    cout << endl;
  }
  return 0;
}
