#include <iostream>
#include <vector>
using namespace std;

int read(const string& s)
{
  int n = 0;
  for (string::const_iterator it = s.begin(); it != s.end(); ++it) {
    n = 2*n + *it-'0';
  }
  return n;
}

int main()
{
  for (string s; cin >> s && s != "ENDOFINPUT";) {
    int N;
    cin >> N;
    string x, y;
    cin >> x >> y;
    int a = read(x) + read(y);
    int m = 0;
    for (int i = 0; i < N; i++) {
      cin >> x;
      m = max(m, read(x) + 255);
    }
    vector<int> bytes(4), nibbles(4);
    for (int i = 0; i < 4; i++) {
      cin >> x;
      bytes[i] = read(x);
    }
    for (int i = 0; i < 4; i++) {
      cin >> x;
      nibbles[i] = read(x);
    }
    cin >> x;

    cout << "HAND " << N << endl;
    vector<int>::const_iterator it = bytes.begin(), jt = nibbles.begin();
    for (int i = 0; i < 4; i++) {
      if (a >= m) {
        break;
      } else if (a < 382) {
        a += *it;
        ++it;
        cout << "Byte me!" << endl;
      } else if (a <= 500) {
        a += *jt;
        ++jt;
        cout << "Nibble me!" << endl;
      } else {
        break;
      }
    }
    if (a > 510) {
      cout << "Bust!" << endl;
    } else if (a >= m) {
        cout << "Win!" << endl;
    } else {
      cout << "Lose!" << endl;
    }
  }
  return 0;
}
