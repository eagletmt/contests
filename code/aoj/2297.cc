#include <iostream>
#include <vector>
#include <queue>
using namespace std;

int main()
{
  int N;
  cin >> N;
  static bool drawable[4][4][4][4];
  for (int i = 0; i < N; i++) {
    int H, W;
    cin >> H >> W;
    for (int k = -H+1; k < 4; k++) {
      for (int l = -W+1; l < 4; l++) {
        drawable[max(0, k)][max(0, l)][min(3, k+H-1)][min(3, l+W-1)] = true;
      }
    }
  }
  vector<string> goal(4);
  for (int i = 0; i < 4; i++) {
    cin >> goal[i];
  }

  queue<int> q;
  q.push(0);
  static const int INF = 1000000;
  vector<int> dist(1<<16, INF);
  dist[0] = 0;
  while (!q.empty()) {
    const int n = q.front();
    q.pop();
    if (n == (1<<16)-1) {
      break;
    }
    for (int i = 0; i < 4; i++) {
      for (int j = 0; j < 4; j++) {
        for (int k = i; k < 4; k++) {
          for (int l = j; l < 4; l++) {
            if (drawable[i][j][k][l]) {
              for (int c = 0; c < 3; c++) {
                static const char rgb[] = "RGB";
                const char cc = rgb[c];
                int next = n;
                for (int x = i; x <= k; x++) {
                  for (int y = j; y <= l; y++) {
                    if (goal[x][y] == cc) {
                      next |= 1 << (4*x+y);
                    } else {
                      next &= ~(1 << (4*x+y));
                    }
                  }
                }
                if (dist[n]+1 < dist[next]) {
                  dist[next] = dist[n]+1;
                  q.push(next);
                }
              }
            }
          }
        }
      }
    }
  }
  cout << dist[(1<<16)-1] << endl;
  return 0;
}
