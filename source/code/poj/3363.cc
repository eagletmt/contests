#include <iostream>
#include <vector>
using namespace std;

void flip(char& c) { if (c == '0') { c = '1'; } else { c = '0'; } }

int solve(vector<string>& pic, int R, int C)
{
  const int N = pic.size(), M = pic[0].size();
  int c = 0;
  for (int i = 0; i+R <= N; i++) {
    for (int j = 0; j+C <= M; j++) {
      if (pic[i][j] == '1') {
        ++c;
        for (int k = 0; k < R; k++) {
          for (int l = 0; l < C; l++) {
            flip(pic[i+k][j+l]);
          }
        }
      }
    }
  }
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < M; j++) {
      if (pic[i][j] == '1') {
        return -1;
      }
    }
  }
  return c;
}

int main()
{
  int N, M, R, C;
  while (cin >> N >> M >> R >> C && N != 0) {
    vector<string> pic(N);
    for (int i = 0; i < N; i++) {
      cin >> pic[i];
    }
    cout << solve(pic, R, C) << endl;
  }
  return 0;
}
