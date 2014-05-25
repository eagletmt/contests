#include <iostream>
#include <vector>
#include <queue>
using namespace std;

struct board
{
  vector<pair<int,int> > holes;
  vector<int> cache;
  board(vector<string>& g, const vector<pair<int,int> >& h)
    : holes(h), cache(1<<h.size())
  {
    build_cache(g);
  }

  void build_cache(vector<string>& grid)
  {
    const int N = holes.size();
    for (int s = 0; s < (1<<N); s++) {
      const int x = __builtin_popcount(s);
      if (N/2 != x && (N+1)/2 != x) {
        continue;
      }
      for (int i = 0; i < N; i++) {
        grid[holes[i].first][holes[i].second] = s & (1<<i) ? '1' : '0';
      }
      cache[s] = evaluate(grid);
    }
  }

  static int evaluate(const vector<string>& grid)
  {
    const int H = grid.size();
    const int W = grid[0].size();
    vector<vector<int> > visited(H, vector<int>(W, false));
    int ans[2] = {0, 0};
    for (int i = 0; i < H; i++) {
      for (int j = 0; j < W; j++) {
        if (visited[i][j]) {
          continue;
        }

        const char c = grid[i][j];
        visited[i][j] = true;
        queue<pair<int,int> > q;
        q.push(make_pair(i, j));
        int d = 0;
        while (!q.empty()) {
          const int k = q.front().first;
          const int l = q.front().second;
          q.pop();
          ++d;
          for (int t = 0; t < 4; t++) {
            static const int di[] = {-1, 1, 0, 0};
            static const int dj[] = {0, 0, -1, 1};
            const int x = k + di[t];
            const int y = l + dj[t];
            if (0 <= x && x < H && 0 <= y && y < W && !visited[x][y] && grid[x][y] == c) {
              visited[x][y] = true;
              q.push(make_pair(x, y));
            }
          }
        }
        ans[c-'0'] = max(ans[c-'0'], d);
      }
    }
    return ans[0] - ans[1];
  }

  pair<int, pair<int,int> > alphabeta(int turn, int alpha = -1000000, int beta = 1000000, int s = 0, int t = 0) const
  {
    const int N = holes.size();
    if (s == (1<<N)-1) {
      return make_pair(turn * cache[t], make_pair(-1, -1));
    }

    pair<int,int> move(-1, -1);
    for (int i = 0; i < N; i++) {
      if (!(s & (1<<i))) {
        const int x = -alphabeta(-turn, -beta, -alpha, s | (1<<i), t | (turn == 1 ? 0 : (1<<i))).first;
        if (x > alpha) {
          alpha = x;
          move = holes[i];
        }
        if (alpha >= beta) {
          return make_pair(alpha, move);
        }
      }
    }
    return make_pair(alpha, move);
  }
};

int main()
{
  int N;
  while (cin >> N && N != 0) {
    vector<string> grid(N);
    vector<pair<int,int> > holes;
    int zero = 0, one = 0;
    for (int i = 0; i < N; i++) {
      cin >> grid[i];
      for (int j = 0; j < N; j++) {
        if (grid[i][j] == '.') {
          holes.push_back(make_pair(i, j));
        } else if (grid[i][j] == '0') {
          ++zero;
        } else {
          ++one;
        }
      }
    }

    const board b(grid, holes);
    const int turn = (N*N - holes.size()) % 2 == 0 ? 1 : -1;
    const pair<int, pair<int,int> > r = b.alphabeta(turn);
    cout << "(" << r.second.first << "," << r.second.second << ") " << r.first << endl;
  }
  return 0;
}
