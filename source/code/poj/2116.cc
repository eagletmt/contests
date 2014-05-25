#include <iostream>
using namespace std;

long long fib[45];

long long decode(const string& s)
{
  long long x = 0;
  const int len = s.size();
  for (int i = 0; i < len; i++) {
    if (s[i] == '1') {
      x += fib[len-i-1];
    }
  }
  return x;
}

string encode(long long x)
{
  if (x == 0) {
    return "0";
  }
  string s(41, '0');
  for (int i = 40; i >= 0; i--) {
    if (x >= fib[i]) {
      s[40-i] = '1';
      x -= fib[i];
    }
  }
  return s.substr(s.find('1'));
}

void times(int n, char c)
{
  for (int i = 0; i < n; i++) {
    cout << c;
  }
}

int main()
{
  fib[0] = 1;
  fib[1] = 2;
  for (int i = 2; i <= 41; i++) {
    fib[i] = fib[i-1] + fib[i-2];
  }

  string a, b;
  while (cin >> a >> b) {
    long long x = decode(a), y = decode(b);
    a = encode(x);
    b = encode(y);
    const string c = encode(x+y);
    int len = c.size();
    cout << "  "; times(len - a.size(), ' '); cout << a << endl;
    cout << "+ "; times(len - b.size(), ' '); cout << b << endl;
    cout << "  "; times(len, '-');  cout << endl;
    cout << "  " << c << endl;
    cout << endl;
  }
  return 0;
}
