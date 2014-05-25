#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main()
{
  int N;
  for (int T = 1; cin >> N && N != 0; T++) {
    string line;
    cin >> line;
    vector<int> cards(N);
    for (int i = 0; i < N; i++) {
      cards[i] = (line[i] == 'U');
    }

    cin >> line;
    vector<int> lp(1, 0), rp(1, N-1);
    int l = 1, r = N-2;
    for (int i = 0; i < N-2; i++) {
      if (line[i] == 'R') {
        reverse(rp.begin(), rp.end());
        for (vector<int>::const_iterator it = rp.begin(); it != rp.end(); ++it) {
          ++cards[*it];
        }
        rp.push_back(r);
        --r;
      } else {
        reverse(lp.begin(), lp.end());
        for (vector<int>::const_iterator it = lp.begin(); it != lp.end(); ++it) {
          ++cards[*it];
        }
        lp.push_back(l);
        ++l;
      }
    }
    vector<int> pile;
    if (line[N-2] == 'R') {
      for (vector<int>::const_reverse_iterator it = rp.rbegin(); it != rp.rend(); ++it) {
        pile.push_back(*it);
        ++cards[*it];
      }
      for (vector<int>::const_iterator it = lp.begin(); it != lp.end(); ++it) {
        pile.push_back(*it);
      }
    } else {
      for (vector<int>::const_reverse_iterator it = lp.rbegin(); it != lp.rend(); ++it) {
        pile.push_back(*it);
        ++cards[*it];
      }
      for (vector<int>::const_iterator it = rp.begin(); it != rp.end(); ++it) {
        pile.push_back(*it);
      }
    }

    int M;
    cin >> M;
    cout << "Pile " << T << endl;
    while (M--) {
      int q;
      cin >> q;
      cout << "Card " << q << " is a face " << (cards[pile[q-1]] % 2 == 1 ? "up" : "down") << " " << pile[q-1]+1 << "." << endl;
    }
  }
  return 0;
}
