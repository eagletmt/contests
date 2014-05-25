#include <iostream>
using namespace std;

int main()
{
  int N;
  while (cin >> N && N != 0) {
    int a[10][10];
    for (int i = 0; i < N; i++) {
      cin >> a[N-1][i];
    }
    int K;
    cin >> K;

    for (int i = N-2; i >= 0; i--) {
      for (int j = 0; j <= i; j++) {
        a[i][j] = a[i+1][j+1] - a[i+1][j];
      }
    }

    for (int i = 0; i < K; i++) {
      for (int j = 0; j < N-1; j++) {
        a[j+1][j+1] += a[j][j];
      }
    }
    cout << "Term " << N+K << " of the sequence is " << a[N-1][N-1] << endl;
  }
  return 0;
}
