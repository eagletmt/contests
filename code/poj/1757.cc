#include <iostream>
using namespace std;

int BinarySearch(int x, int N)
{
  int p, q, i, L;

  p = 0;
  q = N-1;
  L = 0;
  while (p <= q) {
    i = (p + q) / 2;
    ++L;
    if (i == x) {
      return L;
    }
    if (x < i)
      q = i - 1;
    else
      p = i + 1;
  }
  throw "err";
}

int main()
{
  int I, L;
  cin >> I >> L;
  static int ok[10010];
  for (int n = I+1; n <= 10000; n++) {
    int l = BinarySearch(I, n);
    ok[n] = (l == L);
  }
  int cnt = 0;
  for (int n = I+1; n <= 10000; n++) {
    if (ok[n] && !ok[n+1]) {
      ++cnt;
    }
  }
  cout << cnt << endl;
  for (int n = I+1; n <= 10000; n++) {
    if (!ok[n-1] && ok[n]) {
      cout << n;
    }
    if (ok[n] && !ok[n+1]) {
      cout << " " << n << endl;
    }
  }
  return 0;
}
