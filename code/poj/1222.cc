#include <cstdio>
#include <vector>
using namespace std;

struct mod
{
  int m;
  mod(int a) : m(a) {}
  int operator()(int x) const { return ((x%m)+m)%m; }
};

static mod M(2);
int inv_tbl[2] = {-1, 1};

vector<int> gaussian_elimination(vector<vector<int> > a, vector<int> b)
{
  const int N = a.size();
  vector<int> sigma(N);
  for (int i = 0; i < N; i++) {
    sigma[i] = i;
  }

  for (int i = 0; i < N; i++) {
    for (int j = i+1; a[i][i] == 0 && j < N; j++) {
      swap(a[i], a[j]);
      swap(b[i], b[j]);
      swap(sigma[i], sigma[j]);
    }
    if (a[i][i] == 0) {
      continue;
    }

    const int t = inv_tbl[a[i][i]];
    for (int k = i; k < N; k++) {
      a[i][k] = M(a[i][k] * t);
    }
    b[i] = M(b[i] * t);

    for (int j = 0; j < N; j++) {
      if (i == j) {
        continue;
      }
      const int u = a[j][i];
      for (int k = i; k < N; k++) {
        a[j][k] = M(a[j][k] - u*a[i][k]);
      }
      b[j] = M(b[j] - u*b[i]);
    }
  }

  for (int i = 0; i < N; i++) {
    if (a[sigma[i]][sigma[i]] == 0 && b[sigma[i]] != 0) {
      return vector<int>();
    }
  }
  return b;
}

int main()
{
  int T;
  scanf("%d", &T);
  for (int Ti = 1; Ti <= T; Ti++) {
    vector<vector<int> > a(30, vector<int>(30, 0));
    for (int i = 0; i < 5; i++) {
      for (int j = 0; j < 6; j++) {
        for (int d = 0; d < 5; d++) {
          static const int di[] = {0, -1, 1, 0, 0};
          static const int dj[] = {0, 0, 0, -1, 1};
          const int k = i+di[d];
          const int l = j+dj[d];
          if (0 <= k && k < 5 && 0 <= l && l < 6) {
            a[6*i+j][6*k+l] = 1;
          }
        }
      }
    }
    vector<int> b(30);
    for (int i = 0; i < 30; i++) {
      scanf("%d", &b[i]);
    }

    const vector<int> x = gaussian_elimination(a, b);
    printf("PUZZLE #%d\n", Ti);
    if (x.empty()) {
      throw "fail";
    } else {
      for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 6; j++) {
          if (j != 0) {
            putchar(' ');
          }
          printf("%d", x[6*i+j]);
        }
        putchar('\n');
      }
    }
  }
  return 0;
}
