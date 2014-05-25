#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
using namespace std;

map<int,pair<int,int> > cache;

pair<int,int> solve(int start)
{
  if (cache.count(start)) {
    return cache[start];
  }

  vector<int> v;
  for (int i = start; i > 0; i /= 10) {
    v.push_back(i % 10);
  }
  const int N = v.size();

  pair<int,int> ans = make_pair(0, -1);
  for (int s = 1; s < (1<<N)-1; s++) {
    int n = 0;
    for (int i = 0; i < N; i++) {
      if (s & (1<<i)) {
        if (n == 0 && v[N-1-i] == 0) {
          // leading zero
          goto NEXT;
        } else {
          n = 10*n + v[N-1-i];
        }
      }
    }
    if (n > 1 && start % n == 0) {
      int t = 0;
      for (int i = 0; i < N; i++) {
        if ((s & (1<<i)) == 0) {
          t = 10*t + v[N-1-i];
        }
      }
      const pair<int,int> r = solve(t);
      if (ans.first < r.first+1 || (ans.first == r.first+1 && ans.second > t)) {
        ans.first = r.first+1;
        ans.second = t;
        ans.second = t;
      }
    }
NEXT:
    ;
  }
  cache[start] = ans;
  return ans;
}

int main()
{
  int n;
  while (cin >> n && n != 0) {
    pair<int,int> ans = solve(n);
    cout << n;
    while (ans.second != -1) {
      cout << ' ' << ans.second;
      ans = cache[ans.second];
    }
    cout << endl;
  }
  return 0;
}
