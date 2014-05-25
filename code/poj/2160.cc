#include <iostream>
#include <algorithm>
using namespace std;

bool ok(const pair<int,int> *rects)
{
  if (rects[0] != rects[1]) {
    return false;
  }
  if (rects[2] != rects[3]) {
    return false;
  }
  if (rects[4] != rects[5]) {
    return false;
  }

  for (int s = 0; s < (1<<3); s++) {
    pair<int,int> r[3];
    for (int i = 0; i < 3; i++) {
      r[i] = rects[2*i];
      if (s & (1<<i)) {
        swap(r[i].first, r[i].second);
      }
    }
    sort(r, r+3);
    do {
      if (r[0].first == r[1].first
          && r[1].second == r[2].second
          && r[2].first == r[0].second) {
        return true;
      }
    } while (next_permutation(r, r+3));
  }
  return false;
}

int main()
{
  pair<int,int> rects[6];
  for (int i = 0; i < 6; i++) {
    int w, h;
    cin >> w >> h;
    if (w > h) {
      swap(w, h);
    }
    // w <= h
    rects[i].first = w;
    rects[i].second = h;
  }
  sort(rects, rects+6);
  cout << (ok(rects) ? "POSSIBLE" : "IMPOSSIBLE") << endl;
  return 0;
}
