#include <cstdio>
#include <string>
#include <vector>
using namespace std;

int main()
{
  int N, M;
  scanf("%d %d", &N, &M);
  vector<vector<int> > v(N, vector<int>(M));
  int H = 0;
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < M; j++) {
      scanf("%d", &v[i][j]);
      H = max(H, 3*v[i][j]+1 + (N-i)*2);
    }
  }
  const int W = 4*M+1 + 2*N;
  vector<string> view(H, string(W, '.'));
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < M; j++) {
      for (int k = 0; k < v[i][j]; k++) {
        const int left = (N-i-1)*2 + 4*j;
        const int right = left + 4;
        const int below = H-1-(N-1-i)*2 - 3*k;
        const int above = below - 3;
        view[above][left] = view[above][right] = view[below][left] = view[below][right] = '+';
        for (int y = above+1; y < below; y++) {
          view[y][left] = view[y][right] = '|';
          for (int x = left+1; x < right; x++) {
            view[y][x] = ' ';
          }
        }
        for (int x = left+1; x < right; x++) {
          view[above][x] = view[below][x] = '-';
        }

        view[above-1][left+1] = view[above-1][right+1] = '/';
        for (int x = left+2; x < right+1; x++) {
          view[above-1][x] = ' ';
        }
        view[above-2][left+2] = view[above-2][right+2] = '+';
        for (int x = left+3; x < right+2; x++) {
          view[above-2][x] = '-';
        }

        view[below-1][right+1] = '/';
        view[below-2][right+2] = '+';
        view[below-3][right+2] = view[below-4][right+2] = '|';
        view[below-2][right+1] = view[below-3][right+1] = ' ';
      }
    }
  }
  for (int i = 0; i < H; i++) {
    puts(view[i].c_str());
  }
  return 0;
}
