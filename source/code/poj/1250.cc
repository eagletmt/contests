#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

int main()
{
  int n;
  while (cin >> n && n != 0) {
    string seq;
    cin >> seq;
    vector<bool> v(26, false);
    deque<char> q;
    int ans = 0;
    for (string::const_iterator it(seq.begin()); it != seq.end(); ++it) {
      const char c = *it;
      if (!v[c-'A']) {
        // enter
        v[c-'A'] = true;
        if (n == 0) {
          q.push_back(c);
        } else {
          n--;
        }
      } else {
        // leave
        v[c-'A'] = false;
        const deque<char>::iterator p = find(q.begin(), q.end(), c);
        if (p == q.end()) {
          if (q.empty()) {
            n++;
          } else {
            q.pop_front();
          }
        } else {
          q.erase(p);
          ans++;
        }
      }
    }
    if (ans) {
      cout << ans << " customer(s) walked away." << endl;
    } else {
      cout << "All customers tanned successfully." << endl;
    }
  }
  return 0;
}
