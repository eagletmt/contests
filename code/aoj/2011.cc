#include <iostream>
#include <vector>
using namespace std;

int main()
{
  int N;
  while (cin >> N && N != 0) {
    vector<vector<int> > v(N, vector<int>(31, 0));
    for (int i = 0; i < N; i++) {
      int n;
      cin >> n;
      for (int j = 0; j < n; j++) {
        int x;
        cin >> x;
        v[i][x] = 1;
      }
    }

    vector<unsigned long long> w(N, 0);
    for (int i = 0; i < N; i++) {
      w[i] = 1ULL<<i;
    }

    for (int d = 1; d <= 30; d++) {
      vector<int> us(N, 0);
      unsigned long long s = 0ULL;
      for (int i = 0; i < N; i++) {
        for (int j = i+1; j < N; j++) {
          if (v[i][d] && v[j][d]) {
            us[i] = us[j] = 1;
            s |= w[i] | w[j];
          }
        }
      }
      if (s == (1ULL<<N)-1) {
        cout << d << endl;
        goto NEXT;
      }
      for (int i = 0; i < N; i++) {
        if (us[i]) {
          w[i] = s;
        }
      }
    }
    cout << -1 << endl;
NEXT:
    ;
  }
}
