#include <iostream>
using namespace std;

int main()
{
  static const double PI = 3.14159;
  string s;
  while (cin >> s && s != "ENDOFINPUT") {
    double r, g, t;
    cin >> r >> g >> t >> s;
    t = min(t, 360-t);
    const double need = PI*r*t/450;
    if (need < g + 1e-10) {
      cout << "YES " << int(g - need) << endl;
    } else {
      cout << "NO " << int(5*g) << endl;
    }
  }
  return 0;
}
