#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main()
{
  static const int INF = 10000000;
  vector<vector<int> > dist(64, vector<int>(64, INF));
  for (int i = 0; i < 64; i++) {
    dist[i][i] = 0;
    const int x = i/8, y = i%8;
    for (int d = 0; d < 8; d++) {
      static const int dx[] = {1, 2, 2, 1, -1, -2, -2, -1};
      static const int dy[] = {-2, -1, 1, 2, 2, 1, -1, -2};
      const int k = x + dx[d], l = y + dy[d];
      if (0 <= k && k < 8 && 0 <= l && l < 8) {
        dist[i][k*8+l] = 1;
      }
    }
  }
  for (int k = 0; k < 64; k++) {
    for (int i = 0; i < 64; i++) {
      for (int j = 0; j < 64; j++) {
        dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
      }
    }
  }

  string s;
  cin >> s;
  const int king = (s[0]-'A')*8 + s[1]-'1';
  vector<int> knights;
  for (string::size_type i = 2; i < s.size(); i += 2) {
    knights.push_back((s[i]-'A')*8 + s[i+1]-'1');
  }

  int ans = INF;
  for (int i = 0; i < 64; i++) {
    for (int j = 0; j < 64; j++) {
      for (vector<int>::const_iterator it = knights.begin(); it != knights.end(); ++it) {
        int a = abs(king/8 - i/8) + abs(king%8 - i%8) + dist[*it][i];
        for (vector<int>::const_iterator jt = knights.begin(); jt != knights.end(); ++jt) {
          a += jt == it ? dist[i][j] : dist[*jt][j];
        }
        ans = min(ans, a);
      }
    }
  }
  cout << ans << endl;
  return 0;
}
