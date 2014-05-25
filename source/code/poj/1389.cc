#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct rect
{
  int lx, ly, rx, ry;
  bool operator<(const rect& that) const
  {
    return ly < that.ly;
  }
};

int main()
{
  rect r;
  while (cin >> r.lx >> r.ly >> r.rx >> r.ry && r.lx != -1) {
    vector<rect> rs(1, r);
    vector<int> xs;
    xs.push_back(r.lx);
    xs.push_back(r.rx);
    while (cin >> r.lx >> r.ly >> r.rx >> r.ry && r.lx != -1) {
      rs.push_back(r);
      xs.push_back(r.lx);
      xs.push_back(r.rx);
    }

    sort(rs.begin(), rs.end());
    sort(xs.begin(), xs.end());
    const vector<int>::const_iterator last = unique(xs.begin(), xs.end());
    long long ans = 0LL;
    vector<int>::const_iterator it = xs.begin();
    for (vector<int>::const_iterator jt = it++; it != last; ++it, ++jt) {
      const long long w = *it - *jt;
      int l = -1, h = -1;
      for (vector<rect>::const_iterator kt = rs.begin(); kt != rs.end(); ++kt) {
        if (kt->lx <= *jt && *it <= kt->rx) {
          if (l == -1) {
            h = kt->ry;
            l = kt->ly;
          } else if (kt->ly <= h) {
            h = max(h, kt->ry);
          } else {
            ans += w * (h-l);
            h = kt->ry;
            l = kt->ly;
          }
        }
      }
      if (l != -1) {
        ans += w * (h-l);
      }
    }
    cout << ans << endl;
  }
  return 0;
}
