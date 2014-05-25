#include <iostream>
#include <sstream>
#include <vector>
using namespace std;

int main()
{
  string line;
  while (getline(cin, line) && line != "ENDOFINPUT") {
    int M, N;
    {
      istringstream iss(line);
      iss >> line >> M >> N;
    }
    vector<int> deg(N, 0);
    int c = 0;
    for (int i = 0; i < N; i++) {
      getline(cin, line);
      istringstream iss(line);
      int v;
      while (iss >> v) {
        ++deg[i];
        ++deg[v];
        ++c;
      }
    }
    getline(cin, line);

    int odd[2];
    int sz = 0;
    for (int i = 0; i < N; i++) {
      if (deg[i] % 2 == 1) {
        if (sz > 2) {
          ++sz;
        } else {
          odd[sz++] = i;
        }
      }
    }

    if (sz > 2) {
      cout << "NO" << endl;
    } else if (M == 0) {
      if (sz == 0) {
        cout << "YES " << c << endl;
      } else {
        cout << "NO" << endl;
      }
    } else {
      if (sz == 2 && (odd[0] == 0 || odd[1] == 0)) {
        cout << "YES " << c << endl;
      } else {
        cout << "NO" << endl;
      }
    }
  }
  return 0;
}
