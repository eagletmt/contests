#include <iostream>
using namespace std;

int N, cnt;
char ops[20];

void dfs(int n, long long acc = 0, long long x = 1, char op = '+')
{
  if (n == N-1) {
    if (op == '+') {
      acc += x;
    } else {
      acc -= x;
    }
    if (acc == 0) {
      ++cnt;
      if (cnt <= 20) {
        cout << "1";
        for (int i = 0; i < N-1; i++) {
          cout << " " << ops[i] << " " << i+2;
        }
        cout << endl;
      }
    }
  } else {
    long long a = acc + (op == '+' ? x : -x);
    long long y = (n+2 >= 10 ? 100LL : 10LL)*x + n+2;
    ops[n] = '+'; dfs(n+1, a, n+2, '+');
    ops[n] = '-'; dfs(n+1, a, n+2, '-');
    ops[n] = '.'; dfs(n+1, acc, y, op);
  }
}

int main()
{
  cin >> N;
  dfs(0);
  cout << cnt << endl;
  return 0;
}
