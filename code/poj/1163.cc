#include <iostream>
#include <vector>
using namespace std;

int main(void)
{
  int N;
  cin >> N;
  vector<vector<int> > v(N, vector<int>(N));
  for (int i = 0; i < N; i++) {
    for (int j = 0; j <= i; j++) {
      cin >> v[i][j];
    }
  }
  for (int i = N-2; i >= 0; i--) {
    for (int j = 0; j <= i; j++) {
      v[i][j] += max(v[i+1][j], v[i+1][j+1]);
    }
  }
  cout << v[0][0] << endl;
  return 0;
}
