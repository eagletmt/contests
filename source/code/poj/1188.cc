#include <iostream>
#include <algorithm>
using namespace std;

int main()
{
  int N;
  while (cin >> N && N != 0) {
    int x1, x2, y1, y2, z1, z2;
    int d;
    cin >> x1 >> y1 >> z1 >> d;
    x2 = x1+d;
    y2 = y1+d;
    z2 = z1+d;
    for (int i = 1; i < N; i++) {
      int x, y, z;
      cin >> x >> y >> z >> d;
      x1 = max(x1, x);
      x2 = min(x2, x+d);
      y1 = max(y1, y);
      y2 = min(y2, y+d);
      z1 = max(z1, z);
      z2 = min(z2, z+d);
    }
    cout << max(0, (x2-x1)*(y2-y1)*(z2-z1)) << endl;
  }
  return 0;
}
