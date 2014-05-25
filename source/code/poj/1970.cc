#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct board
{
  int grid[19][19];

  bool win_p(int& i, int& j, int self) const
  {
    for (i = 0; i < 19; i++) {
      for (j = 0; j < 19; j++) {
        for (int d = 0; d < 4; d++) {
          int a[5];
          static const int di[] = {-1, 0, 1, 1};
          static const int dj[] = {1, 1, 1, 0};
          for (int k = 0; k < 5; k++) {
            a[k] = at(i + di[d]*k, j + dj[d]*k);
          }
          if (count(a, a+5, self) == 5
              && at(i - di[d], j - dj[d]) != self
              && at(i + di[d]*5, j + dj[d]*5) != self) {
            return true;
          }
        }
      }
    }
    return false;
  }

  int at(int i, int j) const
  {
    if (0 <= i && i < 19 && 0 <= j && j < 19) {
      return grid[i][j];
    } else {
      return 0;
    }
  }
};

int main()
{
  int T;
  cin >> T;
  while (T-- > 0) {
    board b;
    for (int i = 0; i < 19; i++) {
      for (int j = 0; j < 19; j++) {
        cin >> b.grid[i][j];
      }
    }
    int i, j;
    if (b.win_p(i, j, 1)) {
      cout << 1 << endl;
      cout << i+1 << " " << j+1 << endl;
    } else if (b.win_p(i, j, 2)) {
      cout << 2 << endl;
      cout << i+1 << " " << j+1 << endl;
    } else {
      cout << 0 << endl;
    }
  }
  return 0;
}
