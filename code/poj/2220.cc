#include <iostream>
#include <algorithm>
using namespace std;

int main()
{
  for (string dummy; cin >> dummy;) {
    int T, H;
    cin >> T >> H;
    int v[6][8];
    for (int i = 0; i < H; i++) {
      for (int j = 0; j < T; j++) {
        cin >> v[i][j];
      }
    }
    cin >> dummy;

    unsigned S = 1;
    for (int i = 0; i < T; i++) {
      S *= H;
    }
    int mind = 10000000;
    int ans[6][9];
    for (int i = 0; i < H; i++) {
      fill_n(ans[i], T+1, 0);
    }
    for (unsigned s = 0; s < S; s++) {
      int w[6][9];
      int *p[6];
      for (int i = 0; i < H; i++) {
        fill_n(w[i], T+1, 0);
        p[i] = w[i];
      }
      int ttl[6];
      fill_n(ttl, H, 0);
      unsigned t = s;
      for (int i = 0; i < T; i++) {
        *p[t%H] = i+1;
        ++p[t%H];
        ttl[t%H] += v[t%H][i];
        t /= H;
      }
      int hi = 0, lo = 10000000;
      for (int i = 0; i < H; i++) {
        hi = max(hi, ttl[i]);
        lo = min(lo, ttl[i]);
      }
      int d = hi - lo;
      if (d < mind) {
        mind = d;
        for (int i = 0; i < H; i++) {
          copy(w[i], w[i]+T, ans[i]);
        }
      }
    }
    for (int i = 0; i < H; i++) {
      int a = 0;
      bool first = true;
      for (int *p = ans[i]; *p != 0; p++) {
        if (!first) {
          cout << " ";
        }
        first = false;
        cout << *p;
        a += v[i][*p-1];
      }
      if (!first) {
        cout << " ";
      }
      cout << a << endl;
    }
    cout << endl;
  }
  return 0;
}
