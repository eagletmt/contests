#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main()
{
  int N;
  while (cin >> N && N != 0) {
    vector<vector<int> > v(30);
    vector<pair<int,string> > scores(N);
    for (int i = 0; i < N; i++) {
      int c;
      scores[i].first = 0;
      cin >> scores[i].second >> c;
      for (int j = 0; j < c; j++) {
        int m;
        cin >> m;
        v[m].push_back(i);
      }
    }
    for (int i = 0; i < 30; i++) {
      const int s = N - v[i].size() + 1;
      for (vector<int>::const_iterator it = v[i].begin(); it != v[i].end(); ++it) {
        scores[*it].first += s;
      }
    }
    sort(scores.begin(), scores.end());
    cout << scores[0].first << ' ' << scores[0].second << endl;
  }
  return 0;
}
