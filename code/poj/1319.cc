#include <iostream>
#include <cmath>
using namespace std;

int grid(double H, double W)
{
  return static_cast<int>(H) * static_cast<int>(W);
}

int skew(double H, double W)
{
  static const double SQRT3 = sqrt(3.0);
  const int h = 2*(H-1)/SQRT3 + 1;
  const int w1 = W;
  const int w2 = W-0.5;
  return ((h+1)/2)*w1 + (h/2)*w2;
}

int main()
{
  double x, y;
  while (cin >> x >> y) {
    const int g = grid(x, y);
    const int s = max(skew(x, y), skew(y, x));
    if (g >= s) {
      cout << g << " grid" << endl;
    } else {
      cout << s << " skew" << endl;
    }
  }
  return 0;
}
