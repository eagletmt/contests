#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int parse(const vector<string>& subgrid)
{
  unsigned s = 0;
  s |= ((subgrid[1][3] == '-') << 6);
  s |= ((subgrid[2][2] == '|') << 5);
  s |= ((subgrid[2][4] == '|') << 4);
  s |= ((subgrid[3][3] == '-') << 3);
  s |= ((subgrid[4][2] == '|') << 2);
  s |= ((subgrid[4][4] == '|') << 1);
  s |= ((subgrid[5][3] == '-') << 0);
  switch (s) {
    case 19:  return 1;
    case 93:  return 2;
    case 91:  return 3;
    case 58:  return 4;
    case 107: return 5;
    case 111: return 6;
    case 82:  return 7;
    case 127: return 8;
    case 123: return 9;
    default:  throw "unrecognized char";
  }
}

void lr(vector<string>& subgrid)
{
  for (vector<string>::iterator it = subgrid.begin(); it != subgrid.end(); ++it) {
    reverse(it->begin(), it->end());
  }
}

void ud(vector<string>& subgrid)
{
  reverse(subgrid.begin(), subgrid.end());
}

void rot(vector<string>& subgrid)
{
  const vector<string> src(subgrid);
  for (int i = 0; i < 7; i++) {
    for (int j = 0; j < 7; j++) {
      if (src[i][j] == '|') {
        subgrid[6-j][i] = '-';
      } else if (src[i][j] == '-') {
        subgrid[6-j][i] = '|';
      } else {
        subgrid[6-j][i] = src[i][j];
      }
    }
  }
}

int main()
{
  string line;
  while (cin >> line && line != "0") {
    vector<string> lines(1, line);
    for (int i = 1; i < 21; i++) {
      cin >> line;
      lines.push_back(line);
    }
    int d[2][6];
    for (int k = 0; k < 2; k++) {
      static const int tbl[][2] = {{0,7},{7,0},{7,7},{7,14},{7,21},{14,7}};
      for (int i = 0; i < 6; i++) {
        vector<string> grid;
        for (int j = 0; j < 7; j++) {
          grid.push_back(lines[tbl[i][0]+j].substr(tbl[i][1]+29*k, 7));
        }
        switch (i) {
          case 0:
          case 2:
          case 4:
            lr(grid);
            break;
          case 1:
            rot(grid);
            rot(grid);
            rot(grid);
            lr(grid);
            break;
          case 3:
            rot(grid);
            lr(grid);
            break;
          case 5:
            lr(grid);
            ud(grid);
            break;
        }
        d[k][i] = parse(grid);
      }
    }
    int w[2] = {0, 0};
    for (int i = 0; i < 6; i++) {
      for (int j = 0; j < 6; j++) {
        if (d[0][i] > d[1][j]) {
          ++w[0];
        } else if (d[0][i] < d[1][j]) {
          ++w[1];
        }
      }
    }
    cout << (w[0] < w[1] ? "LOW" : "HIGH") << endl;
  }
  return 0;
}
