#include <iostream>
using namespace std;

int main()
{
  int a[31];
  a[0] = 1;
  a[1] = 0;
  for (int i = 2; i <= 30; i++) {
    if (i % 2 == 0) {
      a[i] = 3*a[i-2];
      for (int j = 0; j <= i-4; j += 2) {
        a[i] += 2*a[j];
      }
    } else {
      a[i] = 0;
    }
  }

  int n;
  while (cin >> n && n != -1) {
    cout << a[n] << endl;
  }
  return 0;
}
