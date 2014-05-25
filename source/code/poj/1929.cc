#include <iostream>
#include <sstream>
#include <vector>
#include <cmath>
using namespace std;

int main()
{
  string line;
  while (getline(cin, line) && line != "-") {
    double fat = 0.0;
    double sum = 0.0;
    do {
      istringstream iss(line);
      bool is_percent;
      int val;
      int percent = 100;
      int t = 0;
      for (int i = 0; i < 5; i++) {
        int n;
        char u;
        iss >> n >> u;
        if (u == 'g') {
          static const int tbl[] = {9, 4, 4, 4, 7};
          if (i == 0) {
            is_percent = false;
            val = n * tbl[i];
          }
          t += n * tbl[i];
        } else if (u == 'C') {
          if (i == 0) {
            is_percent = false;
            val = n;
          }
          t += n;
        } else {
          if (i == 0) {
            is_percent = true;
            val = n;
          }
          percent -= n;
        }
      }
      const double ttl = 100.0 * t / percent;
      if (is_percent) {
        fat += ttl * val / 100.0;
      } else {
        fat += val;
      }
      sum += ttl;
    } while (getline(cin, line) && line != "-");
    cout << lround(fat / sum * 100.0) << '%' << endl;
  }
  return 0;
}
