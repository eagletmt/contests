#include <iostream>
#include <vector>
using namespace std;

int main()
{
  int T;
  cin >> T;
  for (int Ti = 1; Ti <= T; Ti++) {
    char grid[9][10];
    vector<pair<int,int> > zeros;
    for (int i = 0; i < 9; i++) {
      cin >> grid[i];
      for (int j = 0; j < 9; j++) {
        if (grid[i][j] == '0') {
          zeros.push_back(make_pair(i, j));
        }
      }
    }

    while (!zeros.empty()) {
      for (vector<pair<int,int> >::iterator it = zeros.begin(); it != zeros.end();) {
        const int i = it->first, j = it->second;
        int s = 45;
        int c = 0;
        for (int k = 0; k < 9; k++) {
          if (grid[k][j] == '0') {
            ++c;
          } else {
            s -= grid[k][j]-'0';
          }
        }
        if (c == 1) {
          grid[i][j] = '0'+s;
          it = zeros.erase(it);
          goto NEXT;
        }

        s = 45; c = 0;
        for (int l = 0; l < 9; l++) {
          if (grid[i][l] == '0') {
            ++c;
          } else {
            s -= grid[i][l]-'0';
          }
        }
        if (c == 1) {
          grid[i][j] = '0'+s;
          it = zeros.erase(it);
          goto NEXT;
        }

        s = 45; c = 0;
        for (int k = 0; k < 3; k++) {
          for (int l = 0; l < 3; l++) {
            if (grid[i-i%3+k][j-j%3+l] == '0') {
              ++c;
            } else {
              s -= grid[i-i%3+k][j-j%3+l]-'0';
            }
          }
        }
        if (c == 1) {
          grid[i][j] = '0'+s;
          it = zeros.erase(it);
          goto NEXT;
        }
        ++it;
NEXT:
        ;
      }
    }

    cout << "Scenario #" << Ti << ":" << endl;
    for (int i = 0; i < 9; i++) {
      cout << grid[i] << endl;
    }
    cout << endl;
  }
  return 0;
}
