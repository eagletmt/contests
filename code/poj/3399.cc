#include <iostream>
#include <vector>
#include <deque>
#include <algorithm>
using namespace std;

int main()
{
  int N, K;
  cin >> N >> K;
  deque<int> pos, neg;
  for (int i = 0; i < N; i++) {
    int x;
    cin >> x;
    if (x >= 0) {
      pos.push_back(x);
    } else {
      neg.push_back(-x);
    }
  }
  if (K % 2 == 1 && pos.empty()) {
    sort(neg.begin(), neg.end());
    for (int i = 0; i < K; i++) {
      if (i != 0) {
        cout << " ";
      }
      cout << -neg[i];
    }
    cout << endl;
    return 0;
  }

  sort(pos.rbegin(), pos.rend());
  sort(neg.rbegin(), neg.rend());

  vector<int> ans;
  if (K % 2 == 1) {
    ans.push_back(pos[0]);
    pos.pop_front();
    K--;
  }
  for (; K > 0; K -= 2) {
    if (pos.size() < 2) {
      ans.push_back(-neg[0]);
      ans.push_back(-neg[1]);
      neg.pop_front();
      neg.pop_front();
    } else if (neg.size() < 2) {
      ans.push_back(pos[0]);
      ans.push_back(pos[1]);
      pos.pop_front();
      pos.pop_front();
    } else {
      const int p = pos[0] * pos[1];
      const int n = neg[0] * neg[1];
      if (p >= n) {
        ans.push_back(pos[0]);
        ans.push_back(pos[1]);
        pos.pop_front();
        pos.pop_front();
      } else {
        ans.push_back(-neg[0]);
        ans.push_back(-neg[1]);
        neg.pop_front();
        neg.pop_front();
      }
    }
  }

  sort(ans.rbegin(), ans.rend());
  for (vector<int>::const_iterator it = ans.begin(); it != ans.end(); ++it) {
    if (it != ans.begin()) {
      cout << " ";
    }
    cout << *it;
  }
  cout << endl;
  return 0;
}
