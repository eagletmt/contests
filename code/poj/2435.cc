#include <iostream>
#include <sstream>
#include <vector>
#include <queue>
using namespace std;

int main()
{
  int H, W;
  cin >> H >> W;
  vector<string> grid(2*H+3, string(2*W+3, '.'));
  queue<pair<int,int> > q;
  static const int INF = 10000000;
  vector<vector<int> > dist(2*H+3, vector<int>(2*W+3, INF));
  vector<vector<int> > prev(2*H+3, vector<int>(2*W+3, -1));
  vector<vector<int> > prev_step(2*H+3, vector<int>(2*W+3, -1));
  for (int i = 1; i <= 2*H; i++) {
    string line;
    cin >> line;
    grid[i] = "." + line + ".";
    for (int j = 1; j <= 2*W; j++) {
      if (grid[i][j] == 'S') {
        q.push(make_pair(i, j));
        dist[i][j] = 0;
      }
    }
  }

  static const int di[] = {-1, 1, 0, 0}, dj[] = {0, 0, -1, 1};
  static const char tbl[] = "NSWE";
  while (!q.empty()) {
    const int i = q.front().first;
    const int j = q.front().second;
    q.pop();
    if (grid[i][j] == 'E') {
      // print
      vector<string> output;
      int k = i, l = j;
      while (dist[k][l] > 0) {
        ostringstream oss;
        oss << tbl[prev[k][l]] << ' ' << prev_step[k][l];
        output.push_back(oss.str());
        int next_k = k - di[prev[k][l]] * (prev_step[k][l]*2);
        int next_l = l - dj[prev[k][l]] * (prev_step[k][l]*2);
        k = next_k;
        l = next_l;
      }
      for (vector<string>::const_reverse_iterator it = output.rbegin(); it != output.rend(); ++it) {
        cout << *it << endl;
      }
      break;
    }

    for (int d = 0; d < 4; d++) {
      int k = i, l = j;
      int step = 0;
      while (true) {
        k += di[d];
        l += dj[d];
        if (grid[k][l] == '.') {
          break;
        }
        k += di[d];
        l += dj[d];
        ++step;
        if (dist[i][j]+step < dist[k][l]) {
          dist[k][l] = dist[i][j]+step;
          prev[k][l] = d;
          prev_step[k][l] = step;
          q.push(make_pair(k, l));
        }
      }
    }
  }
  return 0;
}
