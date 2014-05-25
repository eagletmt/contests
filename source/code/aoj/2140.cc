#include <cstdio>
#include <vector>
using namespace std;

struct mod
{
  int m;
  mod(int a) : m(a) {}
  int operator()(int x) const { return ((x%m)+m)%m; }
};

static mod M(7);
int inv_tbl[7] = {-1, 1, 4, 5, 2, 3, 6};

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
  int N;
  while (scanf("%d", &N) != EOF && N != 0) {
    const mod K(N);
    vector<vector<int> > a(N*N, vector<int>(N*N, 0));
    for (int i = 0; i < N; i++) {
      for (int j = 0; j < N; j++) {
        for (int k = -1; k <= 1; k++) {
          for (int l = -1; l <= 1; l++) {
            a[N*i+j][N*K(i+k)+K(j+l)] = 1;
          }
        }
      }
    }
    vector<int> b(N*N);
    for (int i = 0; i < N*N; i++) {
      scanf("%d", &b[i]);
    }

    const vector<int> x = gaussian_elimination(a, b);
    if (x.empty()) {
      puts("-1");
    } else {
      for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
          if (j != 0) {
            putchar(' ');
          }
          printf("%d", x[N*i+j]);
        }
        putchar('\n');
      }
    }
    putchar('\n');
  }
  return 0;
}
