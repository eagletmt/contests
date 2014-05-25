#include <iostream>
using namespace std;

int main()
{
  int N;
  cin >> N;
  while (N-- > 0) {
    int x, y;
    cin >> x >> y;

    const int d = y-x;
    int i = 0;
    for (; ; i++) {
      if (i % 2 == 0) {
        const long long k = i/2;
        if (d <= k*k + k) {
          break;
        }
      } else {
        const long long k = (i+1)/2;
        if (d <= k*k) {
          break;
        }
      }
    }
    cout << i << endl;
  }
  return 0;
}

