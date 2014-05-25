#include <iostream>
#include <cmath>
using namespace std;

int main()
{
  double A;
  int L;
  cin >> A >> L;

  int ansN, ansD;
  double err = 100;
  for (int D = 1; D <= L; D++) {
    const int N = A*D;
    for (int n = N-1; n <= N+1 && n <= L; n++) {
      const double d = fabs(A - double(n)/D);
      if (d < err) {
        err = d;
        ansN = n;
        ansD = D;
      }
    }
  }
  cout << ansN << ' ' << ansD << endl;
  return 0;
}
