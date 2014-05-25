#include <iostream>
#include <vector>
#include <iterator>
using namespace std;

int main(void)
{
  int M;
  int c = 1;
  while (cin >> M && M != 0) {
    vector<vector<int> > matrix(M, vector<int>(M, 0));
    for (int i = 0; i < M; i++) {
      for (int j = 0; j < M; j++) {
        cin >> matrix[i][j];
      }
    }

    int width = -1;
    for (int i = 0; i < M; i++) {
      if (matrix[0][i] == -1) {
        // vertical
        width += 1+1;
      } else if (matrix[0][i] == 1) {
        // horizontal
        width += 5+1;
      } else {
        width += 3+1;
      }
    }
    const int height = 5+4*(M-2);

    vector<string> square(height, string(width, ' '));

    for (int i = 0; i < M; i++) {
      const int col = 4*i;
      for (int j = 0, pos = 0; j < M; j++, pos++) {
        if (matrix[i][j] == 1) {
          // horizontal
          square[col][pos++] = 'H';
          square[col][pos++] = '-';
          square[col][pos++] = 'O';
          square[col][pos++] = '-';
          square[col][pos++] = 'H';
        } else if (matrix[i][j] == -1) {
          // vertical
          square[col-2][pos] = 'H';
          square[col-1][pos] = '|';
          square[col][pos] = 'O';
          square[col+1][pos] = '|';
          square[col+2][pos] = 'H';
          pos++;
        } else {
          if (pos % 4 != 2) {
            square[col][pos++] = 'H';
            square[col][pos++] = '-';
            square[col][pos] = 'O';
            if (col >= 2 && square[col-2][pos] == ' ') {
              square[col-1][pos] = '|';
              square[col-2][pos] = 'H';
            } else {
              square[col+1][pos] = '|';
              square[col+2][pos] = 'H';
            }
            pos++;
          } else {
            square[col][pos] = 'O';
            if (col >= 2 && square[col-2][pos] == ' ') {
              square[col-1][pos] = '|';
              square[col-2][pos] = 'H';
            } else {
              square[col+1][pos] = '|';
              square[col+2][pos] = 'H';
            }
            pos++;
            square[col][pos++] = '-';
            square[col][pos++] = 'H';
          }
        }
      }
    }

    cout << "Case " << c++ << ':' << endl;
    cout << endl;
    for (int i = 0; i < width+2; i++) {
      cout << '*';
    }
    cout << endl;
    for (int i = 0; i < height; i++) {
      cout << '*' << square[i] << '*' << endl;
    }
    for (int i = 0; i < width+2; i++) {
      cout << '*';
    }
    cout << endl << endl;
  }
  return 0;
}
