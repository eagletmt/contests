#include <iostream>
#include <vector>
using namespace std;

int main(void)
{
  static const int N = 1500;
  vector<int> ugly(N);
  ugly[0] = 1;
  int a = 0, b = 0, c = 0;
  for (int i = 1; i < N; i++) {
    ugly[i] = min(2*ugly[a], min(3*ugly[b], 5*ugly[c]));
    if (ugly[i] == 2*ugly[a]) {
      a++;
    }
    if (ugly[i] == 3*ugly[b]) {
      b++;
    } if (ugly[i] == 5*ugly[c]) {
      c++;
    }
  }

  int n;
  while (cin >> n && n != 0) {
    cout << ugly[n-1] << endl;
  }
  return 0;
}

