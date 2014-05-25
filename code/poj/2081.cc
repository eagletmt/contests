#include <iostream>
#include <vector>
#include <set>
using namespace std;

int main()
{
  static const int N = 500000;
  static int a[N+1];
  set<int> seen;
  seen.insert(0);
  for (int i = 1; i <= N; i++) {
    const int x = a[i-1] - i;
    if (x > 0 && !seen.count(x)) {
      a[i] = x;
    } else {
      a[i] = a[i-1] + i;
    }
    seen.insert(a[i]);
  }

  for (int k; cin >> k && k != -1;) {
    cout << a[k] << endl;
  }
  return 0;
}
