#include <iostream>
using namespace std;

unsigned read(const string& s)
{
  unsigned r = 0;
  for (string::const_iterator it = s.begin(); it != s.end(); ++it) {
    r <<= 2;
    switch (*it) {
      case 'V': r |= 0; break;
      case 'U': r |= 1; break;
      case 'C': r |= 2; break;
      case 'D': r |= 3; break;
      default: throw "unknown number";
    }
  }
  return r;
}

int main()
{
  int N;
  cin >> N;
  cout << "COWCULATIONS OUTPUT" << endl;
  while (N-- > 0) {
    string s;
    cin >> s;
    const unsigned x = read(s);
    cin >> s;
    unsigned y = read(s);
    for (int i = 0; i < 3; i++) {
      cin >> s;
      switch (s[0]) {
        case 'A': y += x; break;
        case 'L': y <<= 2; break;
        case 'R': y >>= 2; break;
        case 'N': break;
        default: throw "unknown operation";
      }
      y = y & ((1<<16)-1);
    }
    cin >> s;
    cout << (y == read(s) ? "YES" : "NO") << endl;
  }
  cout << "END OF OUTPUT" << endl;
  return 0;
}
