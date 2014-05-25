#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;

int main()
{
  int L;
  while (scanf("%d", &L) != EOF) {
    vector<int> v;
    for (int i = 0; i < L; i++) {
      int x;
      scanf("%d", &x);
      const vector<int>::iterator it = lower_bound(v.begin(), v.end(), x);
      if (it == v.end()) {
        v.push_back(x);
      } else {
        *it = x;
      }
    }
    printf("%lu\n", v.size());
  }
  return 0;
}
