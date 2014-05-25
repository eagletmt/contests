#include <iostream>
#include <vector>
using namespace std;

class MineSweeper
{
  int N;
  vector<vector<bool> > mines;
  vector<vector<int> > grid;
  bool lose;

public:
  MineSweeper(const vector<vector<bool> >& m)
    : N(m.size()), mines(m), grid(N, vector<int>(N, -1)), lose(false)
  {}

  void open(int i, int j)
  {
    if (i < 0 || N <= i || j < 0 || N <= j || grid[i][j] >= 0) {
      return;
    }

    if (mines[i][j]) {
      lose = true;
      return;
    }
    int c = 0;
    for (int d = 0; d < 8; d++) {
      static const int di[] = {-1, -1, -1, 0, 1, 1, 1, 0};
      static const int dj[] = {-1, 0, 1, 1, 1, 0, -1, -1};
      const int k = i + di[d];
      const int l = j + dj[d];
      if (0 <= k && k < N && 0 <= l && l < N) {
        if (mines[k][l]) {
          ++c;
        }
      }
    }
    grid[i][j] = c;
  }

  void print(ostream& os)
  {
    for (int i = 0; i < N; i++) {
      for (int j = 0; j < N; j++) {
        if (grid[i][j] >= 0) {
          os << grid[i][j];
        } else if (lose && mines[i][j]) {
          os << '*';
        } else {
          os << '.';
        }
      }
      os << endl;
    }
  }
};

int main()
{
  int N;
  cin >> N;
  vector<vector<bool> > mines(N, vector<bool>(N));
  for (int i = 0; i < N; i++) {
    string s;
    cin >> s;
    for (int j = 0; j < N; j++) {
      mines[i][j] = s[j] == '*';
    }
  }
  MineSweeper ms(mines);
  for (int i = 0; i < N; i++) {
    string s;
    cin >> s;
    for (int j = 0; j < N; j++) {
      if (s[j] == 'x') {
        ms.open(i, j);
      }
    }
  }
  ms.print(cout);
  return 0;
}
