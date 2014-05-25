#include <iostream>
#include <cstdio>
using namespace std;

int main()
{
  int N;
  scanf("%d", &N);

  string a(N, '0'), b(N, '0'), r(N, '0');
  for (int i = 0; i < N; i++) {
    scanf("%d %d", &a[i], &b[i]);
  }
  int c = 0;
  for (int i = N-1; i >= 0; i--) {
    r[i] = c + a[i] + b[i];
    c = r[i] / 10;
    r[i] %= 10;
    r[i] += '0';
  }
  cout << r << endl;

  return 0;
}

