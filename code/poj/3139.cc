#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
using namespace std;

int main()
{
  int n;
  for (int Ti = 1; cin >> n && n != 0; Ti++) {
    int a[16];
    a[0] = n;
    int ix[16];
    ix[0] = 0;
    for (int i = 1; i < 16; i++) {
      cin >> a[i];
      ix[i] = i;
    }

    vector<vector<unsigned> > v(10240);
    do {
      int val = 0;
      unsigned s = 0;
      for (int i = 0; i < 4; i++) {
        val += (i+1) * a[ix[i]];
        s |= 1<<(ix[i]);
      }
      v[val].push_back(s);
      reverse(ix+4, ix+16);
    } while (next_permutation(ix, ix+16));

    static const int M = 1<<16;
    vector<long long> x(M);
    for (int i = 0; i < 10240; i++) {
      const vector<unsigned>& w = v[i];
      const int N = w.size();
      for (int j = 0; j < N; j++) {
        for (int k = j+1; k < N; k++) {
          if ((w[j] & w[k]) == 0) {
            ++x[w[j] | w[k]];
          }
        }
      }
    }

    long long ans = 0LL;
    for (int i = 0; i < M; i++) {
      ans += x[i] * x[i ^ (M-1)];
    }
    cout << "Case " << Ti << ": " << ans/2 << endl;
  }
  return 0;
}
