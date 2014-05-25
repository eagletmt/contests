#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main()
{
  int N, D;
  while (cin >> N >> D && N != 0) {
    vector<int> v(N, true);
    for (int i = 0; i < D; i++) {
      for (int j = 0; j < N; j++) {
        int x;
        cin >> x;
        v[j] = v[j] && x;
      }
    }
    cout << (find(v.begin(), v.end(), true) != v.end() ? "yes" : "no") << endl;
  }
  return 0;
}
