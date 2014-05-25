#include <iostream>
#include <vector>
#include <queue>
#include <complex>
using namespace std;
typedef complex<int> P;

int main()
{
  int R, C, row, col;
  while (cin >> R >> C >> row >> col && !(R == 0 && C == 0 && row == 0 && col == 0)) {
    vector<vector<bool> > grid(R+2, vector<bool>(C+2, false));
    for (int i = 1; i <= R; i++) {
      for (int j = 1; j <= C; j++) {
        char c;
        cin >> c;
        if (c == 'X') {
          grid[i][j] = true;
        }
      }
    }

    vector<vector<bool> > visited(R+1, vector<bool>(C+1, false));
    queue<P> q;
    q.push(P(row, col));
    int perimeter = 0;
    while (!q.empty()) {
      const P p = q.front();  q.pop();
      const int r = real(p);
      const int c = imag(p);
      if (visited[r][c]) {
        continue;
      }

      visited[r][c] = true;
      static const int dir_r[] = {-1, 0, 0, 1, -1, -1, 1, 1};
      static const int dir_c[] = {0, -1, 1, 0, -1, 1, -1, 1};
      for (int i = 0; i < 4; i++) {
        const int s = r + dir_r[i];
        const int d = c + dir_c[i];
        if (!grid[s][d]) {
          perimeter++;
        }
      }
      for (int i = 0; i < 8; i++) {
        const int s = r + dir_r[i];
        const int d = c + dir_c[i];
        if (grid[s][d] && !visited[s][d]) {
          q.push(P(s, d));
        }
      }
    }
    cout << perimeter << endl;
  }
  return 0;
}
