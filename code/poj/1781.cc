#include <iostream>
#include <string>
using namespace std;

int main()
{
  string line;
  while (cin >> line && line != "00e0") {
    long long n = 10*(line[0]-'0') + (line[1]-'0');
    for (int i = 0; i < line[3]-'0'; i++) {
      n *= 10;
    }
    long long b = 1LL;
    for (; b <= n; b *= 2LL);
    b /= 2LL;
    n -= b;
    cout << 2*n+1 << endl;
  }
  return 0;
}
