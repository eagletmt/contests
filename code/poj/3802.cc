#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main()
{
  int W, D;
  while (cin >> W >> D && W != 0) {
    vector<int> ws(W), ds(D);
    for (int i = 0; i < W; i++) {
      cin >> ws[i];
    }
    for (int i = 0; i < D; i++) {
      cin >> ds[i];
    }
    sort(ws.rbegin(), ws.rend());
    sort(ds.rbegin(), ds.rend());

    int ans = 0;
    int i = 0, j = 0;
    while (true) {
      ans += min(ws[i], ds[j]);
      if (i == W-1 && j == D-1) {
        break;
      } else if (i == W-1) {
        j++;
      } else if (j == D-1) {
        i++;
      } else if (ws[i+1] > ds[j+1]) {
        i++;
      } else if (ws[i+1] < ds[j+1]) {
        j++;
      } else if (ws[i+1] == ds[j+1]) {
        i++;
        j++;
      }
    }
    cout << ans << endl;
  }
  return 0;
}
