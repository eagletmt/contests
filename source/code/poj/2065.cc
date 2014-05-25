#include <iostream>
#include <vector>
using namespace std;

struct mod/*{{{*/
{
  int m;
  vector<int> tbl;
  mod(int a) : m(a), tbl(m+1)
  {
    for (int x = 1; x < m; x++) {
      tbl[x] = pow(x, a-2);
    }
  }
  int pow(int x, int e)
  {
    if (e == 0) {
      return 1;
    } else if (e & 1) {
      return (x * pow(x, e-1))%m;
    } else {
      const int y = pow(x, e>>1);
      return (y*y)%m;
    }
  }
  int operator()(int x) const { return ((x%m)+m)%m; }
  int inv(int x) const { return tbl[x]; }
};/*}}}*/

vector<int> gaussian_elimination(vector<vector<int> > a, vector<int> b, const mod& M)/*{{{*/
{
  const int N = a.size();

  for (int i = 0; i < N; i++) {
    for (int j = i+1; a[i][i] == 0 && j < N; j++) {
      swap(a[i], a[j]);
      swap(b[i], b[j]);
    }
    if (a[i][i] == 0) {
      continue;
    }

    const int t = M.inv(a[i][i]);
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
    if (a[i][i] == 0 && b[i] != 0) {
      // no solution
      return vector<int>();
    }
  }
  return b;
}/*}}}*/

int main()
{
  ios::sync_with_stdio(false);
  int T;
  cin >> T;
  while (T-- > 0) {
    int p;
    cin >> p;
    string s;
    cin >> s;
    const int N = s.size();
    mod m(p);
    vector<vector<int> > mat(N, vector<int>(N));
    vector<int> b(N);
    for (int i = 0; i < N; i++) {
      for (int j = 0; j < N; j++) {
        mat[i][j] = m.pow(i+1, j);
      }
      if (s[i] == '*') {
        b[i] = 0;
      } else {
        b[i] = s[i]-'a'+1;
      }
    }

    const vector<int> x = gaussian_elimination(mat, b, m);
    for (vector<int>::const_iterator it = x.begin(); it != x.end(); ++it) {
      if (it != x.begin()) {
        cout << " ";
      }
      cout << *it;
    }
    cout << endl;
  }
  return 0;
}
