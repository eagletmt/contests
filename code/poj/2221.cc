#include <iostream>
#include <algorithm>
using namespace std;

bool ok(int road[10][10])
{
  for (int c = 0; c < 10; c++) {
    for (int i = 1; i < 10; i++) {
      for (int j = 0; j < 10; j++) {
        if (road[i][j] == 0) {
          continue;
        }
        int beg = j + (i-1)*road[i][j];
        int end = j + i*road[i][j];
        if (beg >= end) {
          beg = (beg%10+10)%10;
          end = (end%10+10)%10;
          if (beg >= end) {
            if (end <= c && c <= beg) {
              goto FAILED;
            }
          } else {
            if (c <= beg || end <= c) {
              goto FAILED;
            }
          }
        } else {
          beg = (beg%10+10)%10;
          end = (end%10+10)%10;
          if (beg <= end) {
            if (beg <= c && c <= end) {
              goto FAILED;
            }
          } else {
            if (c <= end || beg <= c) {
              goto FAILED;
            }
          }
        }
      }
    }
    return true;
FAILED:
    ;
  }
  return false;
}

int main()
{
  for (string dummy; cin >> dummy;) {
    int road[10][10];
    fill_n(road[0], 10, 0);
    fill_n(road[9], 10, 0);
    for (int i = 1; i < 9; i++) {
      for (int j = 0; j < 10; j++) {
        cin >> road[i][j];
        if (i <= 4) {
          road[i][j] = -road[i][j];
        }
      }
    }
    cin >> dummy;
    cout << (ok(road) ? "LEFTOVER POSSUM" : "FROGGER") << endl;
  }
  return 0;
}
