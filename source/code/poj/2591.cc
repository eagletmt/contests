#include <iostream>
#include <vector>
using namespace std;

int main(void)
{
  static const int N = 10000000;
  vector<int> v(N);
  int a = 0, b = 0;
  v[0] = 1;
  for (int i = 1; i < N; i++) {
    int x = min(2*v[a]+1, 3*v[b]+1);
    if (x == 2*v[a]+1) {
      a++;
    }
    if (x == 3*v[b]+1) {
      b++;
    }
    v[i] = x;
  }

  int n;
  while (cin >> n) {
    cout << v[n-1] << endl;
  }
  return 0;
}

