#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
using namespace std;

int main()
{
  int T;
  cin >> T;
  while (T-- > 0) {
    int H, L;
    cin >> H >> L;
    map<int, pair<int,int> > cars;
    for (int i = 0; i < H; i++) {
      for (int j = 0; j < L; j++) {
        int r;
        cin >> r;
        if (r != -1) {
          cars.insert(make_pair(r, make_pair(i, j)));
        }
      }
    }

    vector<int> offset(H, 0);
    int ans = 0;
    for (map<int, pair<int,int> >::const_iterator it = cars.begin(); it != cars.end(); ++it) {
      const int h = it->second.first;
      const int l = it->second.second;
      ans += 10*h;
      const int x = abs(l - offset[h]);
      ans += 5*min(x, L - x);
      offset[h] = l;
      ans += 10*h;
    }
    cout << ans << endl;
  }
  return 0;
}
