#include <cstdio>
#include <vector>
using namespace std;

int fact_factor(int n, int p)
{
  int ans = 0;
  while (n != 0) {
    ans += n/p;
    n /= p;
  }
  return ans;
}

void factorize(vector<pair<int,int> >& fs, int m)
{
  for (int i = 2; i*i <= m; i++) {
    if (m % i == 0) {
      int c = 0;
      while (m % i == 0) {
        ++c;
        m /= i;
      }
      fs.push_back(make_pair(i, c));
    }
  }
  if (m != 1) {
    fs.push_back(make_pair(m, 1));
  }
}

bool check(const vector<pair<int,int> >& fs, int N, int K)
{
  for (vector<pair<int,int> >::const_iterator it = fs.begin(); it != fs.end(); ++it) {
    const int p = it->first;
    const int n = it->second;
    if (fact_factor(N, p) - fact_factor(K, p) - fact_factor(N-K, p) < n) {
      return false;
    }
  }
  return true;
}

int main()
{
  int N, M;
  scanf("%d %d", &N, &M);
  vector<pair<int,int> > fs;
  factorize(fs, M);

  vector<int> ans;
  --N;
  for (int i = 0; i <= N; i++) {
    if (check(fs, N, i)) {
      ans.push_back(i+1);
    }
  }
  printf("%lu\n", ans.size());
  for (vector<int>::const_iterator it = ans.begin(); it != ans.end(); ++it) {
    if (it != ans.begin()) {
      putchar(' ');
    }
    printf("%d", *it);
  }
  putchar('\n');
  return 0;
}
