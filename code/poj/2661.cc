#include <iostream>
#include <cmath>
using namespace std;

int main()
{
  int tbl[21];

  for (int i = 0; i < sizeof tbl/sizeof *tbl; i++) {
    const double k = static_cast<double>(4 << i);
    double f = 0.0;
    for (int j = 1;; j++) {
      f += log(static_cast<double>(j)) / log(2);
      if (f > k) {
        tbl[i] = j-1;
        break;
      }
    }
  }

  int y;
  while (cin >> y && y != 0) {
    cout << tbl[(y-1960)/10] << endl;
  }
  return 0;
}
