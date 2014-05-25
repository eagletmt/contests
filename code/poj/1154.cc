#include <iostream>
#include <vector>
#include <set>
#include <stack>
using namespace std;

struct state {
  int row, col, depth;
  bool visited[26];
  state(int r, int c, int d, const bool* v)
    : row(r), col(c), depth(d)
  {
    copy(v, v+26, visited);
  }
};

int main(void)
{
  int R, C;
  cin >> R >> C;

  vector<string> board(R);
  for (int i = 0; i < R; i++) {
    cin >> board[i];
  }

  stack<state> stk;
  bool v[26] = {false};
  v[board[0][0]-'A'] = true;
  stk.push(state(0, 0, 1, v));
  int max_depth = 1;
  while (!stk.empty()) {
    state s = stk.top();
    stk.pop();
    max_depth = max(max_depth, s.depth);

    for (int d = 0; d < 4; d++) {
      static const int dir_r[] = {-1, 0, 0, 1};
      static const int dir_c[] = {0, 1, -1, 0};
      const int r = s.row + dir_r[d];
      const int c = s.col + dir_c[d];
      if (0 <= r && r < R && 0 <= c && c < C && !s.visited[board[r][c]-'A']) {
        s.visited[board[r][c]-'A'] = true;
        stk.push(state(r, c, s.depth+1, s.visited));
        s.visited[board[r][c]-'A'] = false;
      }
    }
  }
  cout << max_depth << endl;
  return 0;
}
