#include <iostream>
#include <vector>
using namespace std;

struct rect
{
  int left, right, top, bottom;
};

vector<vector<rect> > cut_horiz(const vector<vector<rect> >& a, int x)
{
  vector<vector<rect> > b;
  for (vector<vector<rect> >::const_iterator it(a.begin()); it != a.end(); ++it) {
    vector<rect> l, r;
    for (vector<rect>::const_iterator jt(it->begin()); jt != it->end(); ++jt) {
      if (jt->left < x && x < jt->right) {
        // contains
        return a;
      } else if (x <= jt->left) {
        // kt is right
        r.push_back(*jt);
      } else {
        // kt is left
        l.push_back(*jt);
      }
    }
    if (!l.empty()) {
      b.push_back(l);
    }
    if (!r.empty()) {
      b.push_back(r);
    }
  }
  return b;
}

vector<vector<rect> > cut_vert(const vector<vector<rect> >& a, int y)
{
  vector<vector<rect> > b;
  for (vector<vector<rect> >::const_iterator it(a.begin()); it != a.end(); ++it) {
    vector<rect> u, l;
    for (vector<rect>::const_iterator jt(it->begin()); jt != it->end(); ++jt) {
      if (jt->bottom < y && y < jt->top) {
        // contains
        return a;
      } else if (y <= jt->bottom) {
        // kt is upper
        u.push_back(*jt);
      } else {
        // kt is lower
        l.push_back(*jt);
      }
    }
    if (!u.empty()) {
      b.push_back(u);
    }
    if (!l.empty()) {
      b.push_back(l);
    }
  }
  return b;
}

int main()
{
  int T;
  cin >> T;
  while (T-- > 0) {
    int K, P;
    cin >> K >> P;
    vector<rect> v;
    for (int i = 0; i < K; i++) {
      rect r;
      r.left = r.bottom = 100000000;
      r.right = r.top = 0;
      for (int j = 0; j < P; j++) {
        int x, y;
        cin >> x >> y;
        r.left = min(r.left, x-1);
        r.right = max(r.right, x);
        r.bottom = min(r.bottom, y-1);
        r.top = max(r.top, y);
      }
      v.push_back(r);
    }

    vector<vector<rect> > a(1, v);
    for (vector<rect>::const_iterator it(v.begin()); it != v.end(); ++it) {
      a = cut_horiz(a, it->left);
      a = cut_horiz(a, it->right);
      a = cut_vert(a, it->top);
      a = cut_vert(a, it->bottom);
    }
    if (a.size() == K) {
      cout << "YES" << endl;
    } else {
      cout << "NO" << endl;
    }
  }
  return 0;
}
