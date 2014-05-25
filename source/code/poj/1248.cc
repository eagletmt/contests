#include <iostream>
#include <algorithm>
using namespace std;

int f(const string& s)
{
  int n = 0;
  for (int i = 0; i < 5; i++) {
    int x = -1;
    for (int j = 0; j <= i; j++) {
      x *= -(s[i]-'A'+1);
    }
    n += x;
  }
  return n;
}

int main()
{
  int N;
  string s;
  while (cin >> N >> s && N != 0) {
    sort(s.rbegin(), s.rend());
    do {
      if (f(s) == N) {
        cout << s.substr(0, 5) << endl;
        goto NEXT;
      }
      reverse(s.begin()+5, s.end());
    } while (prev_permutation(s.begin(), s.end()));
    cout << "no solution" << endl;
NEXT:
    ;
  }
  return 0;
}
